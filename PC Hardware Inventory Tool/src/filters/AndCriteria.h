#pragma once

#include "IFilterCriteria.h"
#include <memory>

class AndCriteria : public IFilterCriteria {
private:
    std::shared_ptr<IFilterCriteria> left_;
    std::shared_ptr<IFilterCriteria> right_;

public:
    AndCriteria(std::shared_ptr<IFilterCriteria> l,
                std::shared_ptr<IFilterCriteria> r);

    bool matches(const HardwareItem& item) const override;
};
