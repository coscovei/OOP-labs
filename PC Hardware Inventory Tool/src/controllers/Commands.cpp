#include "Commands.h"

// -------------------- AddCommand --------------------

AddCommand::AddCommand(IHardwareRepository* repo, const HardwareItem& item)
    : repo_(repo), item_(item)
{}

// After adding, we fetch the new ID out of the repo's storage.
void AddCommand::execute() {
    // 1) Add to repository (repo will assign a new ID)
    repo_->add(item_);

    // 2) Discover what ID was assigned. We'll assume that
    //    getAll() returns a vector whose last element has the highest ID.
    //    Alternatively, one can scan for max ID.
    auto allItems = repo_->getAll();
    int maxId = 0;
    for (const auto& hw : allItems) {
        if (hw.getId() > maxId) {
            maxId = hw.getId();
        }
    }

    // 3) Overwrite our local item_'s ID so that undo() can remove exactly that ID.
    item_.setId(maxId);
}

void AddCommand::undo() {
    // Now that item_ has the correct ID, remove will succeed.
    repo_->remove(item_.getId());
}


// -------------------- RemoveCommand --------------------

RemoveCommand::RemoveCommand(IHardwareRepository* repo, const HardwareItem& item)
    : repo_(repo), item_(item)
{}

void RemoveCommand::execute() {
    repo_->remove(item_.getId());
}

void RemoveCommand::undo() {
    repo_->add(item_);
}


// -------------------- UpdateCommand --------------------

UpdateCommand::UpdateCommand(IHardwareRepository* repo,
                             const HardwareItem& oldItem,
                             const HardwareItem& newItem)
    : repo_(repo), oldItem_(oldItem), newItem_(newItem)
{}

void UpdateCommand::execute() {
    repo_->update(newItem_);
}

void UpdateCommand::undo() {
    repo_->update(oldItem_);
}
