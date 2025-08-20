#include "Dog.hpp"

Dog::Dog() {
    type = "Dog";
    std::cout << "[Dog] I was born" << std::endl;
}

Dog::~Dog() {
    std::cout << "[Dog] I deid" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "[Dog] Woof! Woof! Woof!" << std::endl;
}