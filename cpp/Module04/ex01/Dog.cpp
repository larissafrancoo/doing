#include "Dog.hpp"

Dog::Dog() {
    type = "Dog";
    brain = new Brain();
    std::cout << "[Dog] I was born" << std::endl;
}

Dog::Dog(const Dog& other) : Animal(other) {
    brain = new Brain(*other.brain);
    std::cout << "[Dog] I was copied" << std::endl;
}

Dog& Dog::operator=(const Dog& other) {
    if (this != &other) {
        Animal::operator=(other);
        delete brain;
        brain = new Brain(*other.brain);
    }
    return *this;
}

Dog::~Dog() {
    delete brain;
    std::cout << "[Dog] I deid" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "[Dog] Woof! Woof! Woof!" << std::endl;
}

void Dog::setIdea(int index, const std::string& idea) {
    brain->setIdea(index, idea);
}

std::string Dog::getIdea(int index) const {
    return brain->getIdea(index);
}