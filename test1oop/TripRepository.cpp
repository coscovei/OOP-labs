//
// Created by matei on 27-Mar-25.
//

#include "TripRepository.h"

#include <iostream>

TripRepository::TripRepository(int cap) {
    capacity = cap;
    trips = new Trip[capacity];
    size = 0;
}

bool TripRepository::add_trip(const Trip& trip) {
    for (int i = 0; i < size; i++) {
        if (trips[i].id == trip.id) {
            std::cout << "Trip already exists" << std::endl;
            return false;
        }
    }
    if (size >= capacity) {
        capacity *= 2;
        Trip* new_trips;
        new_trips = new Trip[capacity];
        for (int i = 0; i < size; i++) {
            new_trips[i] = trips[i];
        }
        delete[] trips;
        trips = new_trips;
    }
    trips[size].id = trip.id;
    trips[size].money = trip.money;
    size++;
    return true;
}

void TripRepository::print_trips(char delimiter) {
    for (int i = 0; i < size; i++) {
        std::cout << trips[i].id << delimiter << trips[i].money << std::endl;
    }
}

MonetaryUnit TripRepository::sum_of_trips() {
    MonetaryUnit sum;
    for (int i = 0; i < size; i++) {
        sum = sum + trips[i].money;
    }
    return sum;
}

TripRepository::~TripRepository() {
    delete[] trips;
    size = NULL;
    capacity = NULL;
}

int TripRepository::count_trips_between(MonetaryUnit from, MonetaryUnit to) {
    int count = 0;
    for (int i = 0; i < size; i++) {
        if ((trips[i].money.compare(from) > 0 && trips[i].money.compare(to) < 0) || trips[i].money.compare(from) == 0 || trips[i].money.compare(to) == 0) {
            count++;
        }
    }
    return count;
}
