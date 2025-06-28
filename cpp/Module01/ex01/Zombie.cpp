#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie(void) {}

Zombie::~Zombie(void) {
	std::cout << "Goodbye, " << name << std::endl;
}

void Zombie::announce(void) {
	std::cout << name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}

void Zombie::setName(std::string name) {
	this->name = name;
}
