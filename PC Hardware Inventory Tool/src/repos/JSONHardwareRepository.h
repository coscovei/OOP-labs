#pragma once

#include "IHardwareRepository.h"
#include <QString>
#include <vector>

class JSONHardwareRepository : public IHardwareRepository {
private:
    QString jsonPath_;
    std::vector<HardwareItem> storage_;
    int nextId_ = 1;

    void loadFromFile();
    void saveToFile() const;

public:
    explicit JSONHardwareRepository(const QString& jsonPath);
    ~JSONHardwareRepository() override;

    void add(const HardwareItem& item) override;
    void remove(int id) override;
    void update(const HardwareItem& item) override;
    HardwareItem findById(int id) const override;
    std::vector<HardwareItem> getAll() const override;
};
