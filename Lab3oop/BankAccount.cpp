//
// Created by matei on 13-Mar-25.
//
#include "BankAccount.h"

BankAccount::BankAccount(const std::string &name, const std::string &number, double initialBalance)
    : accountHolderName(name), accountNumber(number), balance(initialBalance)
{
}

void BankAccount::deposit(double amount)
{
    if (amount > 0)
    {
        balance += amount;
    }
    else
    {
        std::cerr << "Deposit amount must be positive.\n";
    }
}

void BankAccount::withdraw(double amount)
{
    if (amount <= 0)
    {
        std::cerr << "Withdrawal amount must be positive.\n";
    }
    else if (amount > balance)
    {
        std::cerr << "Insufficient funds.\n";
    }
    else
    {
        balance -= amount;
    }
}

std::ostream &operator<<(std::ostream &os, const BankAccount &account)
{
    os << "Account Holder: " << account.accountHolderName << "\n"
       << "Account Number: " << account.accountNumber << "\n"
       << "Current Balance: " << account.balance << "\n";
    return os;
}
