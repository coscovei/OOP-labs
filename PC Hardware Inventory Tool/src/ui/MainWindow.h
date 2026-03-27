#pragma once

#include <QMainWindow>
#include <QTableView>
#include <QToolBar>
#include <QAction>
#include <QHBoxLayout>
#include <QWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QString>                 // Ensure QString is known

#include "../controllers/HardwareController.h"
#include "HardwareTableModel.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

private:
    HardwareController& controller_;
    HardwareTableModel* tableModel_;
    QTableView* tableView_;

    QAction* addAct_;
    QAction* updateAct_;
    QAction* removeAct_;
    QAction* undoAct_;
    QAction* redoAct_;

    QComboBox* categoryFilterCombo_;
    QLineEdit* brandFilterEdit_;
    QLineEdit* modelFilterEdit_;
    QLineEdit* locationFilterEdit_;
    QPushButton* applyFilterBtn_;
    QPushButton* clearFilterBtn_;

    void setupToolbar();
    void setupTable();
    void setupFilterPane();
    void refreshActions();

public:
    explicit MainWindow(HardwareController& ctrl, QWidget* parent = nullptr);
    ~MainWindow() override = default;

    private slots:
        void onAdd();
    void onUpdate();
    void onRemove();
    void onUndo();
    void onRedo();
    void onApplyFilter();
    void onClearFilter();
};
