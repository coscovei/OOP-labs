#include "AddEditDialog.h"
#include <QLabel>

AddEditDialog::AddEditDialog(QWidget* parent)
    : QDialog(parent), currentId_(-1)
{
    setupUI();
}

void AddEditDialog::setupUI()
{
    auto* form = new QFormLayout(this);

    categoryEdit_ = new QLineEdit(this);
    brandEdit_    = new QLineEdit(this);
    modelEdit_    = new QLineEdit(this);
    serialEdit_   = new QLineEdit(this);
    locationEdit_ = new QLineEdit(this);

    quantitySpin_ = new QSpinBox(this);
    quantitySpin_->setMinimum(0);
    quantitySpin_->setMaximum(10000);

    notesEdit_    = new QTextEdit(this);
    notesEdit_->setFixedHeight(80);

    form->addRow(new QLabel("Category:"),     categoryEdit_);
    form->addRow(new QLabel("Brand:"),        brandEdit_);
    form->addRow(new QLabel("Model:"),        modelEdit_);
    form->addRow(new QLabel("Serial #:"),     serialEdit_);
    form->addRow(new QLabel("Location:"),     locationEdit_);
    form->addRow(new QLabel("Quantity:"),     quantitySpin_);
    form->addRow(new QLabel("Notes:"),        notesEdit_);

    okButton_     = new QPushButton("OK", this);
    cancelButton_ = new QPushButton("Cancel", this);
    form->addRow(okButton_, cancelButton_);

    connect(okButton_, &QPushButton::clicked, this, &QDialog::accept);
    connect(cancelButton_, &QPushButton::clicked, this, &QDialog::reject);
}

void AddEditDialog::setItem(const HardwareItem& item)
{
    currentId_ = item.getId();
    categoryEdit_->setText(item.getCategory());
    brandEdit_->setText(item.getBrand());
    modelEdit_->setText(item.getModel());
    serialEdit_->setText(item.getSerialNumber());
    locationEdit_->setText(item.getLocation());
    quantitySpin_->setValue(item.getQuantity());
    notesEdit_->setPlainText(item.getNotes());
}

HardwareItem AddEditDialog::getItem() const
{
    return HardwareItem(
        currentId_,
        categoryEdit_->text(),
        brandEdit_->text(),
        modelEdit_->text(),
        serialEdit_->text(),
        locationEdit_->text(),
        quantitySpin_->value(),
        notesEdit_->toPlainText()
    );
}
