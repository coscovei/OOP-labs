#pragma once
#include <iostream>
#include <vector>


template <typename T>
class Bag {
private:
    std::vector<T> elements;

public:
    void add(const T& item) {
        elements.push_back(item);
    }

    void remove(const T& item) {
        for (auto it = elements.begin(); it != elements.end(); ++it) {
            if (*it == item) {
                elements.erase(it);
                return;
            }
        }
        throw std::out_of_range("Item not found in bag");
    }


    int count(const T& item) const {
        int cnt = 0;
        for (const auto& elem : elements) {
            if (elem == item)
                ++cnt;
        }
        return cnt;
    }

    void print() const {
        std::cout << "{ ";
        for (const auto& elem : elements) {
            std::cout << elem << " ";
        }
        std::cout << "}\n";
    }
};
