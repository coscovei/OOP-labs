cmake_minimum_required(VERSION 3.30)
project(test1oop)

set(CMAKE_CXX_STANDARD 20)

add_executable(test1oop main.cpp
        MonetaryUnit.cpp
        MonetaryUnit.h
        TripRepository.cpp
        TripRepository.h)
