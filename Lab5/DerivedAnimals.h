#ifndef DERIVED_ANIMALS_H
#define DERIVED_ANIMALS_H

#include "Animal.h"

// Mammal class
class Mammal : public Animal {
private:
    bool isAquatic;
    unsigned char gestationPeriod; // in months
public:
    Mammal(const std::string& cName, const std::string& sName, bool aquatic, unsigned char gPeriod);
    virtual void displayInfo() const override;
};

// Bird class
class Bird : public Animal {
private:
    unsigned int wingSpan; // in centimeters
public:
    Bird(const std::string& cName, const std::string& sName, unsigned int wSpan);
    virtual void displayInfo() const override;
};

// Reptile class
class Reptile : public Animal {
private:
    bool isVenomous;
public:
    Reptile(const std::string& cName, const std::string& sName, bool venomous);
    virtual void displayInfo() const override;
};

#endif // DERIVED_ANIMALS_H
