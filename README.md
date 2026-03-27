# OOP Labs Portfolio

A curated collection of **laboratory work and practice projects** completed while studying **Object-Oriented Programming**, starting from structured C exercises and progressing toward **modern C++** and **Qt desktop applications**.

This repository reflects my development as a student programmer: beginning with algorithmic problem solving in C, moving into class design and operator overloading in C++, and ending with GUI-based applications organized into multiple layers.

---

## About This Repository

This project is a semester-style portfolio of assignments and extra work that documents my journey through:

- **procedural programming in C**
- **core OOP concepts in C++**
- **data structures and templates**
- **inheritance and polymorphism**
- **desktop application development with Qt**
- **multi-file project organization using CMake**

Rather than being a single application, this repository is a **collection of independent labs**, each focused on a different topic or milestone in learning OOP and software design.

---

## What I Practiced

Across these labs, I worked on:

- writing clean C and C++ source code
- separating code into headers and implementation files
- designing classes with constructors, methods, and overloaded operators
- implementing custom containers and repositories
- using templates for generic programming
- working with inheritance hierarchies
- building simple graphical interfaces with **Qt**
- organizing larger projects into **models, repositories, controllers, filters, tests, and UI layers**

---

## Repository Structure

### Early Labs
These folders focus on introductory programming and problem solving:

- `Lab1`
- `Lab2`

Main focus:
- C fundamentals
- console applications
- algorithmic thinking
- basic memory and function usage

### Intermediate OOP Labs
These folders mark the transition into object-oriented design:

- `Lab3oop`
- `Lab4oop1`
- `Lab5`
- `test1oop`

Main focus:
- class design
- encapsulation
- constructors and destructors
- operator overloading
- dynamic memory management
- inheritance and derived classes
- repository-style storage

Examples included in this stage:
- a **BankAccount** class
- a custom **Deque** implementation
- an **Animal / derived animals** hierarchy
- a **MonetaryUnit** class and **TripRepository** for storing trips and computing totals

### Advanced OOP / Generic Programming
These folders continue with reusable abstractions and more advanced C++ topics:

- `Lab10`

Main focus:
- templates
- reusable generic containers
- exception handling concepts

Example:
- a templated **Bag** container

### GUI and Application-Oriented Work
These folders move into desktop application development:

- `Lab13`
- `PC Hardware Inventory Tool`

Main focus:
- Qt widgets
- event-driven programming
- controller-based interaction
- multi-layer architecture
- managing collections of domain objects in a UI

Examples:
- a **song manager / playlist-style interface**
- a larger **PC Hardware Inventory Tool** structured into multiple source folders

---

## Highlight Projects

### 1. BankAccount (Lab3oop)
A beginner-friendly OOP project centered on modeling a bank account.

Concepts demonstrated:
- constructors
- private fields
- deposit and withdrawal methods
- formatted output using operator overloading

### 2. Deque Implementation (Lab4oop1)
A custom deque data structure implemented manually.

Concepts demonstrated:
- dynamic arrays
- resizing logic
- copy constructor
- assignment operator
- front/back insertion and removal

### 3. Animal Hierarchy (Lab5)
An inheritance-based exercise using a base class and derived classes.

Concepts demonstrated:
- inheritance
- polymorphism-oriented design
- class extension across multiple files

### 4. MonetaryUnit & TripRepository (test1oop)
A small repository-style C++ project that models money values and stores trip records.

Concepts demonstrated:
- operator overloading for arithmetic
- comparison logic between custom objects
- dynamic repository resizing
- aggregate computations such as totals and filtered counts

### 5. Bag Template (Lab10)
A generic container implemented with templates.

Concepts demonstrated:
- template programming
- generic add/remove/count operations
- reusable class design

### 6. Qt Song Manager (Lab13)
A GUI-based application using Qt widgets to manage songs and a playlist.

Concepts demonstrated:
- QWidget-based UI
- slots and signals workflow
- user interaction through forms, buttons, and lists
- controller-driven updates

### 7. PC Hardware Inventory Tool
The largest and most structured project in the repository.

Concepts demonstrated:
- project layering
- controllers, repositories, models, filters, tests, and UI separation
- larger-scale Qt/C++ application structure
- maintainable organization for a desktop inventory manager

---

## Tech Stack

- **C**
- **C++20**
- **Qt 6**
- **CMake**

---

## Learning Progression

One of the main strengths of this repository is that it shows progression, not just finished code.

It captures how I moved from:

- solving small C exercises
- to designing C++ classes
- to implementing data structures
- to working with templates and inheritance
- to building structured desktop applications with Qt

This makes the repository useful not only as coursework storage, but also as a **personal learning portfolio**.

---

## Notes

Some folders contain IDE-generated build directories such as `cmake-build-debug`. These are included in the repository but are not essential to understanding the source code itself.
