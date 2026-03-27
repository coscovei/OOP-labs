#include <iostream>
#include <limits>
#include "BankAccount.h"

int main() {
    std::string name, accountNumber;
    double initialBalance;

    std::cout << "Enter the account holder's name: ";
    std::getline(std::cin, name);

    std::cout << "Enter the account number: ";
    std::getline(std::cin, accountNumber);

    std::cout << "Enter the initial balance: ";
    while (!(std::cin >> initialBalance)) {
        std::cout << "Please enter a valid number for the balance: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    BankAccount account(name, accountNumber, initialBalance);
    std::cout << "\nAccount created successfully!\n";
    std::cout << account << "\n";

    double depositAmount;
    std::cout << "Enter an amount to deposit: ";
    while (!(std::cin >> depositAmount)) {
        std::cout << "Please enter a valid number for deposit: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    account.deposit(depositAmount);
    std::cout << "\nAfter deposit:\n" << account << "\n";

    double withdrawAmount;
    std::cout << "Enter an amount to withdraw: ";
    while (!(std::cin >> withdrawAmount)) {
        std::cout << "Please enter a valid number for withdrawal: ";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    account.withdraw(withdrawAmount);
    std::cout << "\nAfter withdrawal:\n" << account << "\n";


    return 0;
}
