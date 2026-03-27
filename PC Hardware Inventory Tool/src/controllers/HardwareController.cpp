#include "HardwareController.h"
#include "Commands.h"
#include "../filters/IFilterCriteria.h"

HardwareController::HardwareController(std::unique_ptr<IHardwareRepository> repo)
    : repo_(std::move(repo))
{}

void HardwareController::recordCommand(std::unique_ptr<ICommand> cmd) {
    undoStack_.push(std::move(cmd));
    while (!redoStack_.empty())
        redoStack_.pop();
}

void HardwareController::addItem(const HardwareItem& item) {
    auto cmd = std::make_unique<AddCommand>(repo_.get(), item);
    cmd->execute();
    recordCommand(std::move(cmd));
}

void HardwareController::removeItem(int id) {
    HardwareItem existing = repo_->findById(id);
    auto cmd = std::make_unique<RemoveCommand>(repo_.get(), existing);
    cmd->execute();
    recordCommand(std::move(cmd));
}

void HardwareController::updateItem(const HardwareItem& newItem) {
    HardwareItem oldItem = repo_->findById(newItem.getId());
    auto cmd = std::make_unique<UpdateCommand>(repo_.get(), oldItem, newItem);
    cmd->execute();
    recordCommand(std::move(cmd));
}

std::vector<HardwareItem> HardwareController::getAllItems() const {
    return repo_->getAll();
}

void HardwareController::undo() {
    if (canUndo()) {
        auto cmd = std::move(undoStack_.top());
        undoStack_.pop();
        cmd->undo();
        redoStack_.push(std::move(cmd));
    }
}

void HardwareController::redo() {
    if (canRedo()) {
        auto cmd = std::move(redoStack_.top());
        redoStack_.pop();
        cmd->execute();
        undoStack_.push(std::move(cmd));
    }
}

bool HardwareController::canUndo() const noexcept {
    return !undoStack_.empty();
}

bool HardwareController::canRedo() const noexcept {
    return !redoStack_.empty();
}

std::vector<HardwareItem>
HardwareController::filterItems(std::shared_ptr<IFilterCriteria> criteria) const
{
    std::vector<HardwareItem> results;
    for (const auto& item : repo_->getAll()) {
        if (criteria->matches(item)) {
            results.push_back(item);
        }
    }
    return results;
}
