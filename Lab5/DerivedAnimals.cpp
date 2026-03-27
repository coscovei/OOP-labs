#include "DerivedAnimals.h"
#include <iostream>

// Mammal implementation
Mammal::Mammal(const std::string& cName, const std::string& sName, bool aquatic, unsigned char gPeriod)
    : Animal(cName, sName), isAquatic(aquatic), gestationPeriod(gPeriod) {}

void Mammal::displayInfo() const {
    Animal::displayInfo();
    std::cout << "Is Aquatic: " << (isAquatic ? "Yes" : "No") << std::endl;
    std::cout << "Gestation Period: " << static_cast<int>(gestationPeriod) << " month(s)" << std::endl;
}

// Bird implementation
Bird::Bird(const std::string& cName, const std::string& sName, unsigned int wSpan)
    : Animal(cName, sName), wingSpan(wSpan) {}

void Bird::displayInfo() const {
    Animal::displayInfo();
    std::cout << "Wing Span: " << wingSpan << " cm" << std::endl;
}

// Reptile implementation
Reptile::Reptile(const std::string& cName, const std::string& sName, bool venomous)
    : Animal(cName, sName), isVenomous(venomous) {}

void Reptile::displayInfo() const {
    Animal::displayInfo();
    std::cout << "Is Venomous: " << (isVenomous ? "Yes" : "No") << std::endl;
}
