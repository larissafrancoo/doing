#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : type("WrongAnimal") {
    std::cout << "[WrongAnimal] I exist" << std::endl;
}

WrongAnimal::WrongAnimal(const WrongAnimal& other) {
    *this = other;
    std::cout << "[WrongAnimal] I was copied" << std::endl;
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other) {
    if (this != &other)
        type = other.type;
    return *this;
}

WrongAnimal::~WrongAnimal() {
    std::cout << "[WrongAnimal] I was destroyed" << std::endl;
}

std::string WrongAnimal::getType() const {
    return type;
}

void WrongAnimal::makeSound() const {
    std::cout << "[WrongAnimal] Generic sound" << std::endl;
}