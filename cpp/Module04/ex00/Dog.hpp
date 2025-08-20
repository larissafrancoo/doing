#pragma once
#include "Animal.hpp"

class Dog : public Animal {
public:
    Dog();
    virtual ~Dog();

    void makeSound() const;
};