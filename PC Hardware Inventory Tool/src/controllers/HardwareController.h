#pragma once

#include <memory>
#include <stack>
#include <vector>
#include "../repos/IHardwareRepository.h"
#include "../models/HardwareItem.h"
#include "ICommand.h"

class HardwareController {
private:
    std::unique_ptr<IHardwareRepository> repo_;
    std::stack<std::unique_ptr<ICommand>> undoStack_;
    std::stack<std::unique_ptr<ICommand>> redoStack_;

    void recordCommand(std::unique_ptr<ICommand> cmd);

public:
    explicit HardwareController(std::unique_ptr<IHardwareRepository> repo);

    void addItem(const HardwareItem& item);
    void removeItem(int id);
    void updateItem(const HardwareItem& newItem);

    std::vector<HardwareItem> getAllItems() const;

    std::vector<HardwareItem>
    filterItems(std::shared_ptr<struct IFilterCriteria> criteria) const;

    void undo();
    void redo();
    bool canUndo() const noexcept;
    bool canRedo() const noexcept;
};
