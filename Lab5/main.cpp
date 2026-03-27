#include "Animal.h"
#include "DerivedAnimals.h"
#include <iostream>

int main() {
    Mammal mammal("Tiger", "Panthera tigris", false, 3);
    Bird bird("Eagle", "Haliaeetus leucocephalus", 200);
    Reptile reptile("Cobra", "Naja naja", true);

    // Display information for each animal
    std::cout << "Mammal Info:" << std::endl;
    mammal.displayInfo();
    std::cout << std::endl;

    std::cout << "Bird Info:" << std::endl;
    bird.displayInfo();
    std::cout << std::endl;

    std::cout << "Reptile Info:" << std::endl;
    reptile.displayInfo();
    std::cout << std::endl;

    return 0;
}
