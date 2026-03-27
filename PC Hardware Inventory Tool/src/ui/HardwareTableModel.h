#pragma once

#include <QAbstractTableModel>
#include <vector>
#include "../controllers/HardwareController.h"
#include "../models/HardwareItem.h"

class HardwareTableModel : public QAbstractTableModel {
    Q_OBJECT

private:
    HardwareController& controller_;
    std::vector<HardwareItem> displayedItems_;

public:
    explicit HardwareTableModel(HardwareController& ctrl, QObject* parent = nullptr);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    int columnCount(const QModelIndex& parent = QModelIndex()) const override;

    QVariant data(const QModelIndex& index, int role = Qt::DisplayRole) const override;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const override;

    void refreshAll();
    void refreshFiltered(const std::vector<HardwareItem>& filtered);
};
