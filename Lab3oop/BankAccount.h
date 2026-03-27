//
// Created by matei on 13-Mar-25.
//
#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <string>
#include <iostream>

class BankAccount
{
private:
    std::string accountHolderName;
    std::string accountNumber;
    double balance;

public:
    // Constructor
    BankAccount(const std::string &name, const std::string &number, double initialBalance);

    // Method to deposit funds
    void deposit(double amount);

    // Method to withdraw funds
    void withdraw(double amount);

    // Overloaded stream insertion operator
    friend std::ostream &operator<<(std::ostream &os, const BankAccount &account);
};

#endif

