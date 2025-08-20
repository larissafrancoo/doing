#include "Cat.hpp"

Cat::Cat() {
    type = "Cat";
    std::cout << "[Cat] I was born" << std::endl;
}

Cat::~Cat() {
    std::cout << "[Cat] I died" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "[Cat] Meow! Grrrr...." << std::endl;
}