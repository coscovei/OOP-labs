#pragma once

#include "IFilterCriteria.h"
#include <memory>

class OrCriteria : public IFilterCriteria {
private:
    std::shared_ptr<IFilterCriteria> left_;
    std::shared_ptr<IFilterCriteria> right_;

public:
    OrCriteria(std::shared_ptr<IFilterCriteria> l,
               std::shared_ptr<IFilterCriteria> r);

    bool matches(const HardwareItem& item) const override;
};
