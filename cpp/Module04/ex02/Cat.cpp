#include "Cat.hpp"

Cat::Cat() {
    type = "Cat";
    brain = new Brain();
    std::cout << "[Cat] I was born" << std::endl;
}

Cat::Cat(const Cat& other) : Animal(other) {
    brain = new Brain(*other.brain);
    std::cout << "[Cat] I was copied" << std::endl;
}

Cat& Cat::operator=(const Cat& other) {
    if (this != &other) {
        Animal::operator=(other);
        delete brain;
        brain = new Brain(*other.brain);
    }
    return *this;
}

Cat::~Cat() {
    delete brain;
    std::cout << "[Cat] I died" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "[Cat] Meow! Grrrr...." << std::endl;
}

void Cat::setIdea(int index, const std::string& idea) {
    brain->setIdea(index, idea);
}

std::string Cat::getIdea(int index) const {
    return brain->getIdea(index);
}