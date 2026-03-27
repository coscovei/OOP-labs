#include "Animal.h"

Animal::Animal(const std::string& cName, const std::string& sName)
    : commonName(cName), scientificName(sName) {}


void Animal::displayInfo() const {
    std::cout << "Common Name: " << commonName << std::endl;
    std::cout << "Scientific Name: " << scientificName << std::endl;
}
