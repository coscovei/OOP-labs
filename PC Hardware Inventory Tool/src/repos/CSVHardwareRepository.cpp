#include "CSVHardwareRepository.h"
#include <QFile>
#include <QTextStream>
#include <algorithm>
#include <stdexcept>

CSVHardwareRepository::CSVHardwareRepository(const QString& csvPath)
    : csvPath_(csvPath)
{
    loadFromFile();
}

CSVHardwareRepository::~CSVHardwareRepository()
{
    saveToFile();
}

void CSVHardwareRepository::loadFromFile()
{
    storage_.clear();
    nextId_ = 1;

    QFile file(csvPath_);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        // If missing, create header line
        QFile newFile(csvPath_);
        if (newFile.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&newFile);
            out << "id,category,brand,model,serialNumber,location,quantity,notes\r\n";
            newFile.close();
        }
        return;
    }

    QTextStream in(&file);
    in.readLine(); // skip header

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.trimmed().isEmpty()) continue;

        QStringList parts = line.split(',', Qt::KeepEmptyParts);
        if (parts.size() < 8) continue;

        int id = parts[0].toInt();
        QString category     = parts[1];
        QString brand        = parts[2];
        QString model        = parts[3];
        QString serialNumber = parts[4];
        QString location     = parts[5];
        int quantity         = parts[6].toInt();
        QString notes        = parts[7];

        HardwareItem item(id, category, brand, model,
                          serialNumber, location, quantity, notes);
        storage_.push_back(item);
        nextId_ = std::max(nextId_, id + 1);
    }

    file.close();
}

void CSVHardwareRepository::saveToFile() const
{
    QFile file(csvPath_);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        throw std::runtime_error("Cannot write CSV file: " + csvPath_.toStdString());

    QTextStream out(&file);
    out << "id,category,brand,model,serialNumber,location,quantity,notes\r\n";
    for (const auto& item : storage_) {
        out << item.getId()           << ','
            << item.getCategory()     << ','
            << item.getBrand()        << ','
            << item.getModel()        << ','
            << item.getSerialNumber() << ','
            << item.getLocation()     << ','
            << item.getQuantity()     << ','
            << item.getNotes()        << "\r\n";
    }

    file.close();
}

void CSVHardwareRepository::add(const HardwareItem& item)
{
    HardwareItem copy = item;
    if (copy.getId() <= 0) {
        copy.setId(nextId_++);
    } else {
        for (const auto& existing : storage_) {
            if (existing.getId() == copy.getId()) {
                throw std::runtime_error("ID conflict while adding to CSV repository");
            }
        }
        nextId_ = std::max(nextId_, copy.getId() + 1);
    }
    storage_.push_back(copy);
    saveToFile();
}

void CSVHardwareRepository::remove(int id)
{
    auto it = std::find_if(storage_.begin(), storage_.end(),
                           [id](const HardwareItem& item) { return item.getId() == id; });
    if (it == storage_.end()) {
        throw std::runtime_error("Item ID not found in CSV repository");
    }
    storage_.erase(it);
    saveToFile();
}

void CSVHardwareRepository::update(const HardwareItem& item)
{
    auto it = std::find_if(storage_.begin(), storage_.end(),
                           [&item](const HardwareItem& existing) {
                               return existing.getId() == item.getId();
                           });
    if (it == storage_.end()) {
        throw std::runtime_error("Item ID not found in CSV repository");
    }
    *it = item;
    saveToFile();
}

HardwareItem CSVHardwareRepository::findById(int id) const
{
    auto it = std::find_if(storage_.begin(), storage_.end(),
                           [id](const HardwareItem& item) { return item.getId() == id; });
    if (it == storage_.end()) {
        throw std::runtime_error("Item ID not found in CSV repository");
    }
    return *it;
}

std::vector<HardwareItem> CSVHardwareRepository::getAll() const
{
    return storage_;
}
