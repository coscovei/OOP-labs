#pragma once
#include <iostream>

#ifndef DEQUE_H
#define DEQUE_H

class Deque {
private:
    int* data;
    int capacity, size, front, rear;
    void resize();

public:
    // Constructor
    Deque(int cap = 10);
    // Destructor
    ~Deque();
    // Copy Constructor
    Deque(const Deque& other);
    // Copy Assignment Operator
    Deque& operator=(const Deque& other);

    void push_front(int value);
    void push_back(int value);
    void pop_front();
    void pop_back();
    int top() const;
    int back() const;

    // Overloaded Output Operator
    friend std::ostream& operator<<(std::ostream& os, const Deque& dq);
};

#endif // DEQUE_H
