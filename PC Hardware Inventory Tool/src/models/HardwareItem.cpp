#include "HardwareItem.h"

HardwareItem::HardwareItem(int id,
                           const QString& category,
                           const QString& brand,
                           const QString& model,
                           const QString& serialNumber,
                           const QString& location,
                           int quantity,
                           const QString& notes)
    : id_(id),
      category_(category),
      brand_(brand),
      model_(model),
      serialNumber_(serialNumber),
      location_(location),
      quantity_(quantity),
      notes_(notes)
{}

int HardwareItem::getId() const noexcept {
    return id_;
}
void HardwareItem::setId(int id) noexcept {
    id_ = id;
}

const QString& HardwareItem::getCategory() const noexcept {
    return category_;
}
void HardwareItem::setCategory(const QString& c) noexcept {
    category_ = c;
}

const QString& HardwareItem::getBrand() const noexcept {
    return brand_;
}
void HardwareItem::setBrand(const QString& b) noexcept {
    brand_ = b;
}

const QString& HardwareItem::getModel() const noexcept {
    return model_;
}
void HardwareItem::setModel(const QString& m) noexcept {
    model_ = m;
}

const QString& HardwareItem::getSerialNumber() const noexcept {
    return serialNumber_;
}
void HardwareItem::setSerialNumber(const QString& s) noexcept {
    serialNumber_ = s;
}

const QString& HardwareItem::getLocation() const noexcept {
    return location_;
}
void HardwareItem::setLocation(const QString& l) noexcept {
    location_ = l;
}

int HardwareItem::getQuantity() const noexcept {
    return quantity_;
}
void HardwareItem::setQuantity(int q) noexcept {
    quantity_ = q;
}

const QString& HardwareItem::getNotes() const noexcept {
    return notes_;
}
void HardwareItem::setNotes(const QString& n) noexcept {
    notes_ = n;
}

bool HardwareItem::operator==(const HardwareItem& other) const noexcept {
    return id_ == other.id_;
}
