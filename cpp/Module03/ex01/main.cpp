#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main() {
    std::cout << "Teste claptrap ----------------------------------------------------------------" << std::endl;
    ClapTrap clap("WALL-E");
    clap.attack("GO-4");
    clap.takeDamage(5);
    clap.beRepaired(3);
    std::cout << "Teste scavtrap ----------------------------------------------------------------" << std::endl;
    ScavTrap scav("EVE");
    scav.attack("AUTO");
    scav.takeDamage(20);
    scav.beRepaired(10);
    scav.guardGate();
    std::cout << "Teste attack sem energia scavtrap ---------------------------------------------" << std::endl;
    for (int i = 0; i < 50; ++i) scav.attack("R2-D2");
    scav.attack("C-3PO");
    scav.guardGate();
    return 0;
}