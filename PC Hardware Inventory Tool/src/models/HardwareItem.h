#pragma once

#include <QString>

class HardwareItem {
private:
    int id_;
    QString category_;
    QString brand_;
    QString model_;
    QString serialNumber_;
    QString location_;
    int quantity_;
    QString notes_;

public:
    HardwareItem(int id,
                 const QString& category,
                 const QString& brand,
                 const QString& model,
                 const QString& serialNumber,
                 const QString& location,
                 int quantity,
                 const QString& notes);

    int getId() const noexcept;
    void setId(int id) noexcept;

    const QString& getCategory() const noexcept;
    void setCategory(const QString& c) noexcept;

    const QString& getBrand() const noexcept;
    void setBrand(const QString& b) noexcept;

    const QString& getModel() const noexcept;
    void setModel(const QString& m) noexcept;

    const QString& getSerialNumber() const noexcept;
    void setSerialNumber(const QString& s) noexcept;

    const QString& getLocation() const noexcept;
    void setLocation(const QString& l) noexcept;

    int getQuantity() const noexcept;
    void setQuantity(int q) noexcept;

    const QString& getNotes() const noexcept;
    void setNotes(const QString& n) noexcept;

    bool operator==(const HardwareItem& other) const noexcept;
};
