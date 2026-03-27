#ifndef ANIMAL_H
#define ANIMAL_H

#include <string>
#include <iostream>

class Animal {
protected:
    std::string commonName;
    std::string scientificName;
public:
    Animal(const std::string& cName, const std::string& sName);
    virtual void displayInfo() const;
};

#endif // ANIMAL_H
