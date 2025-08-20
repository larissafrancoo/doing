#include "Animal.hpp"

Animal::Animal() : type("Animal") {
    std::cout << "[Animal] I exist" << std::endl;
}

Animal::Animal(const Animal& other) {
    *this = other;
    std::cout << "[Animal] I was copied" << std::endl;
}

Animal& Animal::operator=(const Animal& other) {
    if (this != &other)
        type = other.type;
    return *this;
}

Animal::~Animal() {
    std::cout << "[Animal] I was destroyed" << std::endl;
}

std::string Animal::getType() const {
    return type;
}

void Animal::makeSound() const {
    std::cout << "[Animal] Generic Sound" << std::endl;
}