#include "FragTrap.hpp"

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    hitPoints = 100;
    energyPoints = 100;
    attackDamage = 30;
    std::cout << "FragTrap " << name << " has been constructed!" << std::endl;
}

FragTrap::FragTrap(const FragTrap& other) : ClapTrap(other) {
    *this = other;
    std::cout << "FragTrap " << name << " copied from another!" << std::endl;
}

FragTrap& FragTrap::operator=(const FragTrap& other) {
    if (this != &other) {
        ClapTrap::operator=(other); 
    }
    return *this;
}

FragTrap::~FragTrap() {
    std::cout << "[fragtrap] Goodbye, " << name << "... **Destroyed**" << std::endl;
}

void FragTrap::attack(const std::string& target) {
    if (hitPoints <= 0 || energyPoints <= 0) {
        std::cout << "FragTrap " << name << " can't attack " << target << ": no hit points or energy left." << std::endl;
        return;
    }
    energyPoints--;
    std::cout << "FragTrap " << name << " launches a powerful attack on " << target << ", dealing " << attackDamage << " points of damage!" << std::endl;
}

void FragTrap::highFivesGuys(void) {
    std::cout << "FragTrap " << name << " is asking for a high five! ✋" << std::endl;
}