#include "Deque.h"

// Private member function to resize the deque.
void Deque::resize() {
    int* newData = new int[capacity * 2];
    for (int i = 0; i < size; i++) {
        newData[i] = data[(front + i) % capacity];
    }
    delete[] data;  // Correct deletion of the allocated array.
    data = newData;
    front = 0;
    rear = size - 1;
    capacity *= 2;
}

// Constructor
Deque::Deque(int cap) : capacity(cap), size(0), front(0), rear(-1) {
    data = new int[capacity];
}

// Destructor
Deque::~Deque() {
    delete[] data;
}

// Copy Constructor
Deque::Deque(const Deque& other){
    data = new int[other.capacity];
    for (int i = 0; i < other.capacity; i++) {
        data[i] = other.data[i];
    }
    size = other.size;
    front = other.front;
    rear = other.rear;
    capacity = other.capacity;
}

// Copy Assignment Operator
Deque& Deque::operator=(const Deque& other) {
    if (this == &other)
        return *this;

    delete[] data;
    capacity = other.capacity;
    size = other.size;
    front = other.front;
    rear = other.rear;
    data = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        data[i] = other.data[i];
    }
    return *this;
}

void Deque::push_front(int value) {
    if (size == capacity)
        resize();
    front = (front - 1 + capacity) % capacity;
    data[front] = value;
    size++;
}

void Deque::push_back(int value) {
    if (size == capacity)
        resize();
    rear = (rear + 1) % capacity;
    data[rear] = value;
    size++;
}

void Deque::pop_front() {
    if (size == 0)
        return;
    front = (front + 1) % capacity;
    size--;
}

void Deque::pop_back() {
    if (size == 0)
        return;
    rear = (rear - 1 + capacity) % capacity;
    size--;
}

int Deque::top() const {
    return (size > 0) ? data[front] : -1;
}

int Deque::back() const {
    return (size > 0) ? data[rear] : -1;
}

// Overloaded output operator for printing the deque.
std::ostream& operator<<(std::ostream& os, const Deque& dq) {
    if (dq.size == 0) {
        os << "Deque is empty";
    } else {
        for (int i = 0; i < dq.size; i++) {
            os << dq.data[(dq.front + i) % dq.capacity] << " ";
        }
    }
    return os;
}
