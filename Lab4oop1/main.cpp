#include "Deque.h"


void testDeque() {

    Deque deque1;

    // Test empty deque operations
    std::cout << "Empty Deque, deque1: " << deque1 << std::endl;

    // Test inserting elements
    deque1.push_back(1);
    deque1.push_back(2);
    deque1.push_front(3);
    deque1.push_front(4);
    deque1.push_front(5);
    std::cout << "After insertions, deque1: " << deque1 << std::endl;

    // Test popping elements
    deque1.pop_front();
    std::cout << "After popping front: " << deque1 << std::endl;
    deque1.pop_back();
    std::cout << "After popping back: " << deque1 << std::endl;

    std::cout << "Front element: " << deque1.top() << std::endl;
    std::cout << "Back element: " << deque1.back() << std::endl;

    // Test deep copy
    Deque deque2 = deque1;
    std::cout << "Copied Deque, deque2: " << deque2 << std::endl;

    // Test copy assignment
    Deque deque3;
    deque3.push_back(10);
    deque3.push_back(20);
    deque3.push_back(30);
    std::cout << "After insertions, deque3: " << deque3 << std::endl;

    deque3=deque1;
    std::cout << "Assigned Deque, deque3: " << deque3 << std::endl;

    std::cout << "All tests completed successfully!" << std::endl;
}

int main() {
    testDeque();
    return 0;
}