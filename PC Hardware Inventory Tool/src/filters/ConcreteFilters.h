#pragma once

#include "IFilterCriteria.h"
#include <QString>

// CategoryCriteria: exact match, case-insensitive
class CategoryCriteria : public IFilterCriteria {
private:
    QString desiredCategory_;

public:
    explicit CategoryCriteria(const QString& cat);
    bool matches(const HardwareItem& item) const override;
};

// BrandCriteria: “contains” (case-insensitive)
class BrandCriteria : public IFilterCriteria {
private:
    QString desiredBrandLower_;

public:
    explicit BrandCriteria(const QString& brand);
    bool matches(const HardwareItem& item) const override;
};

// ModelContainsCriteria: “contains” (case-insensitive)
class ModelContainsCriteria : public IFilterCriteria {
private:
    QString desiredModelLower_;

public:
    explicit ModelContainsCriteria(const QString& model);
    bool matches(const HardwareItem& item) const override;
};

// LocationCriteria: “contains” (case-insensitive)
class LocationCriteria : public IFilterCriteria {
private:
    QString desiredLocationLower_;

public:
    explicit LocationCriteria(const QString& loc);
    bool matches(const HardwareItem& item) const override;
};
