#pragma once
#include "Animal.hpp"

class Cat : public Animal {
public:
    Cat();
    virtual ~Cat();

    void makeSound() const;
};