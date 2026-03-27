// File: src/ui/MainWindow.cpp

#include "MainWindow.h"
#include "AddEditDialog.h"
#include "../filters/ConcreteFilters.h"
#include "../filters/AndCriteria.h"

#include <QHeaderView>
#include <QItemSelectionModel>
#include <QItemSelection>    // Required for QItemSelection
#include <QVBoxLayout>
#include <QMessageBox>
#include <QKeySequence>
#include <QString>           // Ensure QString is known

MainWindow::MainWindow(HardwareController& ctrl, QWidget* parent)
    : QMainWindow(parent), controller_(ctrl)
{
    QWidget* central = new QWidget(this);
    auto* mainLayout = new QHBoxLayout(central);

    setupFilterPane();
    mainLayout->addWidget(categoryFilterCombo_->parentWidget());

    setupTable();
    mainLayout->addWidget(tableView_, 1);

    setCentralWidget(central);
    setupToolbar();
    refreshActions();

    setWindowTitle("PC Hardware Inventory");
    resize(900, 600);
}

void MainWindow::setupToolbar()
{
    auto* toolbar = new QToolBar(this);
    addToolBar(toolbar);

    addAct_    = toolbar->addAction("Add");
    updateAct_ = toolbar->addAction("Update");
    removeAct_ = toolbar->addAction("Remove");
    toolbar->addSeparator();

    undoAct_ = toolbar->addAction("Undo");
    undoAct_->setShortcut(QKeySequence::Undo);   // Ctrl+Z
    undoAct_->setToolTip("Undo (Ctrl+Z)");

    redoAct_ = toolbar->addAction("Redo");
    redoAct_->setShortcut(QKeySequence::Redo);   // Ctrl+Y or Ctrl+Shift+Z
    redoAct_->setToolTip("Redo (Ctrl+Y)");

    connect(addAct_,    &QAction::triggered, this, &MainWindow::onAdd);
    connect(updateAct_, &QAction::triggered, this, &MainWindow::onUpdate);
    connect(removeAct_, &QAction::triggered, this, &MainWindow::onRemove);
    connect(undoAct_,   &QAction::triggered, this, &MainWindow::onUndo);
    connect(redoAct_,   &QAction::triggered, this, &MainWindow::onRedo);

    updateAct_->setEnabled(false);
    removeAct_->setEnabled(false);

    connect(
        tableView_->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        this,
        [this](const QItemSelection & /*selected*/, const QItemSelection & /*deselected*/) {
            bool has = !tableView_->selectionModel()->selectedRows().isEmpty();
            updateAct_->setEnabled(has);
            removeAct_->setEnabled(has);
        }
    );
}

void MainWindow::setupTable()
{
    tableView_ = new QTableView(this);
    tableModel_ = new HardwareTableModel(controller_, this);
    tableView_->setModel(tableModel_);

    tableView_->setSelectionBehavior(QAbstractItemView::SelectRows);
    tableView_->setSelectionMode(QAbstractItemView::SingleSelection);
    tableView_->setEditTriggers(QAbstractItemView::NoEditTriggers);

    tableView_->horizontalHeader()->setStretchLastSection(true);
}

void MainWindow::setupFilterPane()
{
    QWidget* filterWidget = new QWidget(this);
    auto* filterLayout = new QVBoxLayout(filterWidget);

    categoryFilterCombo_ = new QComboBox(filterWidget);
    categoryFilterCombo_->addItem("");
    categoryFilterCombo_->addItems({ "CPU", "GPU", "RAM", "Motherboard", "Storage", "PSU", "Case", "Peripheral" });

    brandFilterEdit_    = new QLineEdit(filterWidget);
    modelFilterEdit_    = new QLineEdit(filterWidget);
    locationFilterEdit_ = new QLineEdit(filterWidget);

    applyFilterBtn_ = new QPushButton("Apply Filter", filterWidget);
    clearFilterBtn_ = new QPushButton("Clear Filter", filterWidget);

    filterLayout->addWidget(new QLabel("Category:", filterWidget));
    filterLayout->addWidget(categoryFilterCombo_);
    filterLayout->addWidget(new QLabel("Brand contains:", filterWidget));
    filterLayout->addWidget(brandFilterEdit_);
    filterLayout->addWidget(new QLabel("Model contains:", filterWidget));
    filterLayout->addWidget(modelFilterEdit_);
    filterLayout->addWidget(new QLabel("Location:", filterWidget));
    filterLayout->addWidget(locationFilterEdit_);
    filterLayout->addWidget(applyFilterBtn_);
    filterLayout->addWidget(clearFilterBtn_);
    filterLayout->addStretch();

    connect(applyFilterBtn_, &QPushButton::clicked, this, &MainWindow::onApplyFilter);
    connect(clearFilterBtn_, &QPushButton::clicked, this, &MainWindow::onClearFilter);

    filterWidget->setLayout(filterLayout);
}

void MainWindow::onAdd()
{
    AddEditDialog dlg(this);
    if (dlg.exec() == QDialog::Accepted) {
        HardwareItem newItem = dlg.getItem();
        try {
            controller_.addItem(newItem);
            tableModel_->refreshAll();
            QMessageBox::information(this, "Success", "Item added.");
        } catch (const std::exception& ex) {
            QMessageBox::critical(this, "Error", ex.what());
        }
        refreshActions();
    }
}

void MainWindow::onUpdate()
{
    auto sel = tableView_->selectionModel()->selectedRows();
    if (sel.isEmpty())
        return;

    int row = sel.first().row();
    int id  = tableModel_->data(tableModel_->index(row, 0)).toInt();
    HardwareItem existing = controller_.getAllItems().at(static_cast<size_t>(row));

    AddEditDialog dlg(this);
    dlg.setItem(existing);

    if (dlg.exec() == QDialog::Accepted) {
        HardwareItem updated = dlg.getItem();
        try {
            controller_.updateItem(updated);
            tableModel_->refreshAll();
            QMessageBox::information(this, "Success", "Item updated.");
        } catch (const std::exception& ex) {
            QMessageBox::critical(this, "Error", ex.what());
        }
        refreshActions();
    }
}

void MainWindow::onRemove()
{
    auto sel = tableView_->selectionModel()->selectedRows();
    if (sel.isEmpty())
        return;

    int row = sel.first().row();
    int id  = tableModel_->data(tableModel_->index(row, 0)).toInt();

    QString questionText = QString("Are you sure you want to remove item ID %1?").replace("%1", QString::number(id));
    auto reply = QMessageBox::question(
        this,
        QString("Confirm Removal"),
        questionText,
        QMessageBox::Yes | QMessageBox::No
    );
    if (reply == QMessageBox::Yes) {
        try {
            controller_.removeItem(id);
            tableModel_->refreshAll();
            QMessageBox::information(this, QString("Success"), QString("Item removed."));
        } catch (const std::exception& ex) {
            QMessageBox::critical(this, QString("Error"), ex.what());
        }
        refreshActions();
    }
}

void MainWindow::onUndo()
{
    controller_.undo();
    tableModel_->refreshAll();
    refreshActions();
}

void MainWindow::onRedo()
{
    controller_.redo();
    tableModel_->refreshAll();
    refreshActions();
}

void MainWindow::onApplyFilter()
{
    std::shared_ptr<IFilterCriteria> crit = nullptr;

    if (!categoryFilterCombo_->currentText().isEmpty()) {
        auto c = std::make_shared<CategoryCriteria>(categoryFilterCombo_->currentText());
        if (crit) crit = std::make_shared<AndCriteria>(crit, c);
        else      crit = c;
    }
    if (!brandFilterEdit_->text().isEmpty()) {
        auto b = std::make_shared<BrandCriteria>(brandFilterEdit_->text());
        if (crit) crit = std::make_shared<AndCriteria>(crit, b);
        else      crit = b;
    }
    if (!modelFilterEdit_->text().isEmpty()) {
        auto m = std::make_shared<ModelContainsCriteria>(modelFilterEdit_->text());
        if (crit) crit = std::make_shared<AndCriteria>(crit, m);
        else      crit = m;
    }
    if (!locationFilterEdit_->text().isEmpty()) {
        auto l = std::make_shared<LocationCriteria>(locationFilterEdit_->text());
        if (crit) crit = std::make_shared<AndCriteria>(crit, l);
        else      crit = l;
    }

    if (crit) {
        auto filtered = controller_.filterItems(crit);
        tableModel_->refreshFiltered(filtered);
    } else {
        tableModel_->refreshAll();
    }
}

void MainWindow::onClearFilter()
{
    categoryFilterCombo_->setCurrentIndex(0);
    brandFilterEdit_->clear();
    modelFilterEdit_->clear();
    locationFilterEdit_->clear();
    tableModel_->refreshAll();
}

void MainWindow::refreshActions()
{
    undoAct_->setEnabled(controller_.canUndo());
    redoAct_->setEnabled(controller_.canRedo());
}
