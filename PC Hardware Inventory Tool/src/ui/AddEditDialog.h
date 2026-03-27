#pragma once

#include <QDialog>
#include <QLineEdit>
#include <QSpinBox>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include "../models/HardwareItem.h"

class AddEditDialog : public QDialog {
    Q_OBJECT

private:
    QLineEdit* categoryEdit_;
    QLineEdit* brandEdit_;
    QLineEdit* modelEdit_;
    QLineEdit* serialEdit_;
    QLineEdit* locationEdit_;
    QSpinBox* quantitySpin_;
    QTextEdit* notesEdit_;
    QPushButton* okButton_;
    QPushButton* cancelButton_;
    int currentId_; // -1 for new, otherwise existing ID

public:
    explicit AddEditDialog(QWidget* parent = nullptr);

    void setItem(const HardwareItem& item);
    HardwareItem getItem() const;

private:
    void setupUI();
};
