#include <iostream>
#include "TripRepository.h"

int main() {
    // test MonetaryUnit

    // test default constructor
    MonetaryUnit money1;
    std::cout << money1 << std::endl;

    //test parameterised constructor
    MonetaryUnit money2(2, 'f');
    std::cout << money2 << std::endl;

    // test get_fils
    std::cout << money2.get_fils() << std::endl;

    // test get
    std::cout << money2.get('D') << std::endl;

    // test plus overload
    MonetaryUnit money3(3, 'D');
    MonetaryUnit money4(5, 'f');
    std::cout << money2+money3+money4 << std::endl;

    //test minus overload
    std::cout << money3 - money4 << std::endl;

    // test compare
    std::cout << money3.compare(money4) << std::endl;
    std::cout << money4.compare(money3) << std::endl;

    // finish test MonetaryUnit

    //test TripRepository

    TripRepository repo(5); // test parameterised constructor
    Trip Trip1;
    Trip Trip2;
    Trip Trip3;
    Trip Trip4;
    Trip Trip5;
    Trip Trip6;
    Trip1.id = 1;
    Trip2.id = 1;
    Trip3.id = 3;
    Trip4.id = 4;
    Trip5.id = 5;
    Trip6.id = 6;
    MonetaryUnit money5(10, 'D');
    MonetaryUnit money6(63, 'f');
    Trip1.money = money1;
    Trip2.money = money2;
    Trip3.money = money3;
    Trip4.money = money4;
    Trip5.money = money5;
    Trip6.money = money6;
    repo.add_trip(Trip1); // test add_trip
    repo.add_trip(Trip2);
    repo.add_trip(Trip3);
    repo.add_trip(Trip4);
    repo.add_trip(Trip5);
    repo.add_trip(Trip6);

    repo.print_trips('/'); // test print_trips
    std::cout << repo.sum_of_trips() << std::endl; // test sum_of_trips
    std::cout << repo.count_trips_between(money4, money5) << std::endl; // test count_trips_between

    repo.~TripRepository();
    repo.print_trips('/');
    // test repository deletion
}

