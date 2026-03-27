#include "HardwareTableModel.h"

HardwareTableModel::HardwareTableModel(HardwareController& ctrl, QObject* parent)
    : QAbstractTableModel(parent), controller_(ctrl)
{
    displayedItems_ = controller_.getAllItems();
}

int HardwareTableModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return static_cast<int>(displayedItems_.size());
}

int HardwareTableModel::columnCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return 8; // ID, Category, Brand, Model, Serial, Location, Quantity, Notes
}

QVariant HardwareTableModel::data(const QModelIndex& index, int role) const {
    if (!index.isValid() || role != Qt::DisplayRole)
        return {};

    const HardwareItem& item = displayedItems_.at(static_cast<size_t>(index.row()));
    switch (index.column()) {
        case 0: return item.getId();
        case 1: return item.getCategory();
        case 2: return item.getBrand();
        case 3: return item.getModel();
        case 4: return item.getSerialNumber();
        case 5: return item.getLocation();
        case 6: return item.getQuantity();
        case 7: return item.getNotes();
        default: return {};
    }
}

QVariant HardwareTableModel::headerData(int section, Qt::Orientation orientation,
                                        int role) const {
    if (role != Qt::DisplayRole || orientation != Qt::Horizontal)
        return {};

    static const QString headers[] = {
        "ID", "Category", "Brand", "Model",
        "Serial Number", "Location", "Quantity", "Notes"
    };
    if (section < 0 || section >= 8) return {};
    return headers[section];
}

void HardwareTableModel::refreshAll() {
    beginResetModel();
    displayedItems_ = controller_.getAllItems();
    endResetModel();
}

void HardwareTableModel::refreshFiltered(const std::vector<HardwareItem>& filtered) {
    beginResetModel();
    displayedItems_ = filtered;
    endResetModel();
}
