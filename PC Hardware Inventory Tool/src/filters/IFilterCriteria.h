#pragma once

#include "../models/HardwareItem.h"

struct IFilterCriteria {
    virtual ~IFilterCriteria() = default;
    virtual bool matches(const HardwareItem& item) const = 0;
};
