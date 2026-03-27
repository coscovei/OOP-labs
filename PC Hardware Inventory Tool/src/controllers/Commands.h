#pragma once

#include "ICommand.h"
#include "../repos/IHardwareRepository.h"
#include "../models/HardwareItem.h"

// AddCommand
class AddCommand : public ICommand {
private:
    IHardwareRepository* repo_;
    HardwareItem item_;  // we will update this with the real ID after adding

public:
    AddCommand(IHardwareRepository* repo, const HardwareItem& item);
    void execute() override;
    void undo() override;
};

// RemoveCommand
class RemoveCommand : public ICommand {
private:
    IHardwareRepository* repo_;
    HardwareItem item_; // store removed item for undo

public:
    RemoveCommand(IHardwareRepository* repo, const HardwareItem& item);
    void execute() override;
    void undo() override;
};

// UpdateCommand
class UpdateCommand : public ICommand {
private:
    IHardwareRepository* repo_;
    HardwareItem oldItem_;
    HardwareItem newItem_;

public:
    UpdateCommand(IHardwareRepository* repo,
                  const HardwareItem& oldItem,
                  const HardwareItem& newItem);
    void execute() override;
    void undo() override;
};
