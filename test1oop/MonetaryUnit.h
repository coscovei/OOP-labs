//
// Created by matei on 27-Mar-25.
//

#ifndef MONETARYUNIT_H
#define MONETARYUNIT_H
#include <ostream>


class MonetaryUnit {
protected:
    int fils;
public:
    MonetaryUnit();
    MonetaryUnit(int amount, char unit);
    int get_fils();
    int get(char unit);
    MonetaryUnit operator+(const MonetaryUnit& other);
    MonetaryUnit operator-(const MonetaryUnit& other);
    int compare(const MonetaryUnit& other);

    friend std::ostream& operator<<(std::ostream& os, const MonetaryUnit& obj);
};



#endif //MONETARYUNIT_H
