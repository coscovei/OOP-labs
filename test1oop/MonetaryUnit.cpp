//
// Created by matei on 27-Mar-25.
//

#include "MonetaryUnit.h"

#include <iostream>

MonetaryUnit::MonetaryUnit() {
    fils = 0;
}

MonetaryUnit::MonetaryUnit(int amount, char unit) {
    if (unit == 'f') {
        fils = amount;
    }
    else if (unit == 'D') {
        fils = amount*100;
    }
    else {
        std::cout << "Unrecognized unit" << std::endl;
    }
}

int MonetaryUnit::get_fils() {
    return fils;
}

int MonetaryUnit::get(char unit) {
    if (unit == 'f') {
        return fils;
    }
    else if (unit == 'D') {
        return fils/100;
    }
    else {
        std::cout << "Unrecognized unit" << std::endl;
        return 0;
    }
}

MonetaryUnit MonetaryUnit::operator+(const MonetaryUnit &other) {
    return(MonetaryUnit(fils + other.fils, 'f'));
}

MonetaryUnit MonetaryUnit::operator-(const MonetaryUnit &other) {
    return(MonetaryUnit(fils - other.fils, 'f'));
}

int MonetaryUnit::compare(const MonetaryUnit &other) {
    if (fils < other.fils) {
        return -1;
    }
    else if (fils > other.fils) {
        return 1;
    }
    else {
        return 0;
    }
}

std::ostream& operator<<(std::ostream& os, const MonetaryUnit &obj) {
    if (obj.fils < 100) {
        os << obj.fils << "f" << std::endl;
    }
    else {
        if (obj.fils%100 == 0) {
            os << obj.fils/100 << "D" << std::endl;
        }
        else {
            os << obj.fils/100 << "D" << obj.fils%100 << "f" << std::endl;
        }
    }
    return os;
}


