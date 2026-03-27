#include "AndCriteria.h"

AndCriteria::AndCriteria(std::shared_ptr<IFilterCriteria> l,
                         std::shared_ptr<IFilterCriteria> r)
    : left_(std::move(l)), right_(std::move(r))
{}

bool AndCriteria::matches(const HardwareItem& item) const {
    return left_->matches(item) && right_->matches(item);
}
