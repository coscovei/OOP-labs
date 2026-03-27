// File: src/tests/RepoControllerTests.cpp

#include <cassert>
#include <iostream>

#include <cstdio>    // for std::remove
#include <QString>
#include <QDir>

#include "../repos/CSVHardwareRepository.h"
#include "../repos/JSONHardwareRepository.h"
#include "../controllers/HardwareController.h"
#include "../models/HardwareItem.h"
#include "../filters/ConcreteFilters.h"
#include "../filters/AndCriteria.h"
#include "../filters/OrCriteria.h"

// ----------------------------------------------------------------------------
// Helper: Remove a file if it exists (ignore errors).
// ----------------------------------------------------------------------------
static void safeRemoveFile(const QString& qpath) {
    // Convert to std::string for std::remove
    std::string path = qpath.toStdString();
    std::remove(path.c_str());
}

// ----------------------------------------------------------------------------
// Test CSVHardwareRepository (add, findById, update, remove, getAll).
// ----------------------------------------------------------------------------
static void testCSVRepository() {
    std::cout << "[Test] CSV repository...\n";
    // Use a simple file name in the current working directory
    QString csvPath = "test_repo.csv";

    safeRemoveFile(csvPath);
    CSVHardwareRepository repo(csvPath);

    // Initially empty
    assert(repo.getAll().empty());

    // Add one item
    HardwareItem item1(0, "CPU", "Intel", "i7-9700K", "SN123", "Lab", 5, "Notes1");
    repo.add(item1);

    {
        auto all = repo.getAll();
        assert(all.size() == 1);
        int assignedId = all[0].getId();
        assert(assignedId > 0);

        // findById
        HardwareItem found = repo.findById(assignedId);
        assert(found.getBrand() == QString("Intel"));
        assert(found.getQuantity() == 5);

        // update quantity 5→10
        HardwareItem updated(assignedId, "CPU", "Intel", "i7-9700K", "SN123", "Lab", 10, "Notes1-upd");
        repo.update(updated);
        HardwareItem fetched2 = repo.findById(assignedId);
        assert(fetched2.getQuantity() == 10);
        assert(fetched2.getNotes() == QString("Notes1-upd"));

        // remove
        repo.remove(assignedId);
        assert(repo.getAll().empty());

        // removing again should throw
        bool threw = false;
        try {
            repo.remove(assignedId);
        } catch (const std::runtime_error&) {
            threw = true;
        }
        assert(threw);
    }

    // Add two more to check unique IDs
    HardwareItem a(0, "RAM", "Corsair", "Vengeance", "SN200", "Office", 8, "");
    HardwareItem b(0, "GPU", "AMD", "RX 580", "SN201", "Office", 2, "");
    repo.add(a);
    repo.add(b);
    {
        auto all = repo.getAll();
        assert(all.size() == 2);
        std::vector<int> ids;
        for (auto& hw : all) {
            ids.push_back(hw.getId());
            assert(hw.getId() > 0);
        }
        assert(ids[0] != ids[1]);
    }

    safeRemoveFile(csvPath);
    std::cout << "[Pass] CSV repository\n";
}

// ----------------------------------------------------------------------------
// Test JSONHardwareRepository (same checks).
// ----------------------------------------------------------------------------
static void testJSONRepository() {
    std::cout << "[Test] JSON repository...\n";
    QString jsonPath = "test_repo.json";

    safeRemoveFile(jsonPath);
    JSONHardwareRepository repo(jsonPath);

    assert(repo.getAll().empty());

    HardwareItem item1(0, "Storage", "Samsung", "EVO 860", "SN300", "Desk", 4, "");
    repo.add(item1);
    {
        auto all = repo.getAll();
        assert(all.size() == 1);
        int assignedId = all[0].getId();
        assert(assignedId > 0);

        HardwareItem fetched = repo.findById(assignedId);
        assert(fetched.getBrand() == QString("Samsung"));
        assert(fetched.getQuantity() == 4);

        HardwareItem upd(assignedId, "Storage", "Samsung", "EVO 870", "SN300", "Desk", 8, "Upgraded");
        repo.update(upd);
        HardwareItem fetched2 = repo.findById(assignedId);
        assert(fetched2.getQuantity() == 8);
        assert(fetched2.getNotes() == QString("Upgraded"));

        repo.remove(assignedId);
        assert(repo.getAll().empty());
        bool threw = false;
        try {
            repo.remove(assignedId);
        } catch (const std::runtime_error&) {
            threw = true;
        }
        assert(threw);
    }

    HardwareItem x(0, "PSU", "EVGA", "SuperNOVA", "SN400", "Server", 3, "");
    HardwareItem y(0, "Case", "NZXT", "H510", "SN401", "Shop", 2, "");
    repo.add(x);
    repo.add(y);
    {
        auto all = repo.getAll();
        assert(all.size() == 2);
        auto id0 = all[0].getId();
        auto id1 = all[1].getId();
        assert(id0 != id1);
    }

    safeRemoveFile(jsonPath);
    std::cout << "[Pass] JSON repository\n";
}

// ----------------------------------------------------------------------------
// Test HardwareController (addItem, updateItem, removeItem, undo/redo, filter).
// ----------------------------------------------------------------------------
static void testControllerLogic() {
    std::cout << "[Test] HardwareController...\n";

    QString csvPath = "test_ctrl.csv";
    safeRemoveFile(csvPath);
    auto repo = std::make_unique<CSVHardwareRepository>(csvPath);
    HardwareController ctrl(std::move(repo));

    // Add + undo/redo
    HardwareItem it0(0, "GPU", "NVIDIA", "RTX 3070", "SN500", "Lab", 7, "");
    ctrl.addItem(it0);
    {
        auto all1 = ctrl.getAllItems();
        assert(all1.size() == 1);
        int id1 = all1[0].getId();
        assert(id1 > 0);

        ctrl.undo();
        assert(ctrl.getAllItems().empty());

        ctrl.redo();
        auto all2 = ctrl.getAllItems();
        assert(all2.size() == 1);
        assert(all2[0].getModel() == QString("RTX 3070"));
    }

    // Update + undo/redo
    {
        auto all = ctrl.getAllItems();
        int id = all[0].getId();

        HardwareItem upd(id, "GPU", "NVIDIA", "RTX 3070", "SN500", "Lab", 10, "");
        ctrl.updateItem(upd);
        auto all3 = ctrl.getAllItems();
        assert(all3.size() == 1);
        assert(all3[0].getQuantity() == 10);

        ctrl.undo();
        auto all4 = ctrl.getAllItems();
        assert(all4[0].getQuantity() == 7);

        ctrl.redo();
        auto all5 = ctrl.getAllItems();
        assert(all5[0].getQuantity() == 10);
    }

    // Remove + undo/redo
    {
        auto all = ctrl.getAllItems();
        int id0 = all[0].getId();

        HardwareItem it1(0, "RAM", "Corsair", "Vengeance", "SN600", "Office", 4, "");
        ctrl.addItem(it1);
        auto allBefore = ctrl.getAllItems();
        assert(allBefore.size() == 2);

        int id1 = (allBefore[0].getId() == id0 ? allBefore[1].getId() : allBefore[0].getId());

        ctrl.removeItem(id1);
        auto allAfterRem = ctrl.getAllItems();
        assert(allAfterRem.size() == 1);
        assert(allAfterRem[0].getId() == id0);

        ctrl.undo();
        auto allUndoRem = ctrl.getAllItems();
        assert(allUndoRem.size() == 2);

        ctrl.redo();
        auto allRedoRem = ctrl.getAllItems();
        assert(allRedoRem.size() == 1);
        assert(allRedoRem[0].getId() == id0);
    }

    // Filtering
    {
        while (!ctrl.getAllItems().empty()) {
            int id = ctrl.getAllItems().back().getId();
            ctrl.removeItem(id);
        }
        assert(ctrl.getAllItems().empty());

        ctrl.addItem(HardwareItem(0, "CPU", "AMD", "Ryzen 7", "SN800", "Desk", 3, ""));
        ctrl.addItem(HardwareItem(0, "GPU", "AMD", "RX 5600", "SN801", "Desk", 1, ""));
        ctrl.addItem(HardwareItem(0, "RAM", "Kingston", "HyperX", "SN802", "Server", 16, ""));

        auto amdCrit = std::make_shared<BrandCriteria>("AMD");
        auto amdList = ctrl.filterItems(amdCrit);
        assert(amdList.size() == 2);
        for (auto& hw : amdList) {
            assert(hw.getBrand().toLower().contains("amd"));
        }

        auto cpuCrit = std::make_shared<CategoryCriteria>("CPU");
        auto combo  = std::make_shared<AndCriteria>(amdCrit, cpuCrit);
        auto cpuAmdList = ctrl.filterItems(combo);
        assert(cpuAmdList.size() == 1);
        assert(cpuAmdList[0].getCategory() == QString("CPU"));
        assert(cpuAmdList[0].getBrand() == QString("AMD"));

        auto kingCrit = std::make_shared<BrandCriteria>("Kingston");
        auto orCrit   = std::make_shared<OrCriteria>(cpuCrit, kingCrit);
        auto orList   = ctrl.filterItems(orCrit);
        assert(orList.size() == 2);
    }

    safeRemoveFile(csvPath);
    std::cout << "[Pass] HardwareController tests\n";
}

// ----------------------------------------------------------------------------
// Entry point: call all three test routines.
// ----------------------------------------------------------------------------
void runRepoControllerTests() {
    std::cout << "==== Repo/Controller Smoke Tests ====\n";
    testCSVRepository();
    testJSONRepository();
    testControllerLogic();
    std::cout << "==== All Repo/Controller tests passed! ====\n\n";
}
