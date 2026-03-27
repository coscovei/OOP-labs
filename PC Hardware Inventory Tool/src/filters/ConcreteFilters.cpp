#include "ConcreteFilters.h"

// CategoryCriteria
CategoryCriteria::CategoryCriteria(const QString& cat)
    : desiredCategory_(cat)
{}
bool CategoryCriteria::matches(const HardwareItem& item) const {
    return item.getCategory()
               .compare(desiredCategory_, Qt::CaseInsensitive) == 0;
}

// BrandCriteria
BrandCriteria::BrandCriteria(const QString& brand)
    : desiredBrandLower_(brand.toLower())
{}
bool BrandCriteria::matches(const HardwareItem& item) const {
    return item.getBrand().toLower().contains(desiredBrandLower_);
}

// ModelContainsCriteria
ModelContainsCriteria::ModelContainsCriteria(const QString& model)
    : desiredModelLower_(model.toLower())
{}
bool ModelContainsCriteria::matches(const HardwareItem& item) const {
    return item.getModel().toLower().contains(desiredModelLower_);
}

// LocationCriteria
LocationCriteria::LocationCriteria(const QString& loc)
    : desiredLocationLower_(loc.toLower())
{}
bool LocationCriteria::matches(const HardwareItem& item) const {
    return item.getLocation().toLower().contains(desiredLocationLower_);
}
