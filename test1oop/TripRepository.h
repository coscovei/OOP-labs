//
// Created by matei on 27-Mar-25.
//

#ifndef TRIPREPOSITORY_H
#define TRIPREPOSITORY_H
#include "MonetaryUnit.h"

class Trip {
public:
    int id;
    MonetaryUnit money;
};


class TripRepository {
private:
    Trip* trips;
    int size;
    int capacity;
public:
    TripRepository(int cap);
    bool add_trip(const Trip& trip);
    void print_trips(char delimiter);
    MonetaryUnit sum_of_trips();
    ~TripRepository();
    int count_trips_between(MonetaryUnit from, MonetaryUnit to);

};


#endif //TRIPREPOSITORY_H
