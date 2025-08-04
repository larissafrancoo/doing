#include "ClapTrap.hpp"
#include "FragTrap.hpp"

int main() {
    std::cout << "Teste claptrap ----------------------------------------------------------------" << std::endl;
    ClapTrap clap("EVE");
    clap.attack("WALL-E");
    clap.takeDamage(5);
    clap.beRepaired(3);

    std::cout << "Teste fragtrap ----------------------------------------------------------------" << std::endl;
    FragTrap frag("Baymax");
    frag.attack("Ameca");
    frag.takeDamage(40);
    frag.beRepaired(20);
    frag.highFivesGuys();

    std::cout << "Teste attack sem energia fragtrap ---------------------------------------------" << std::endl;
    for (int i = 0; i < 100; ++i) frag.attack("Minions");
    frag.attack("Gru");
    frag.highFivesGuys();
    return 0;
}