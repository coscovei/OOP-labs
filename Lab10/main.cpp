#include <iostream>
#include "bag.h"
#include <string>

int main() {

    Bag<int> intBag;
    intBag.add(1);
    intBag.add(2);
    intBag.add(1);
    intBag.print();
    try{intBag.remove(2);}
    catch(const std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }
    intBag.print();

    Bag<std::string> stringBag;
    stringBag.add("car");
    stringBag.add("truck");
    stringBag.add("pickup");
    stringBag.print();

    Bag<double> doubleBag;
    doubleBag.add(12.31);
    doubleBag.add(5.68);
    doubleBag.add(0.25);
    doubleBag.print();
    try{doubleBag.remove(12.32);}
    catch(const std::out_of_range &e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
