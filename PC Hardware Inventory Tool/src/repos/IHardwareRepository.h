#pragma once

#include "../models/HardwareItem.h"
#include <vector>

class IHardwareRepository {
public:
    virtual ~IHardwareRepository() = default;

    virtual void add(const HardwareItem& item) = 0;
    virtual void remove(int id) = 0;
    virtual void update(const HardwareItem& item) = 0;
    virtual HardwareItem findById(int id) const = 0;
    virtual std::vector<HardwareItem> getAll() const = 0;
};
