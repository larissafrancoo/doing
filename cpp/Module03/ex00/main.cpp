#include "ClapTrap.hpp"

int main() {
    ClapTrap robot("Frank (o puxa frango)");

    std::cout << "Teste padrão -------------------------------------------------------------------------" << std::endl;
    robot.attack("Pica Pau");
    robot.takeDamage(4);
    robot.beRepaired(2);
    std::cout << "Teste attack sem energia -------------------------------------------------------------" << std::endl;
    for (int i = 0; i < 10; ++i) robot.attack("Papa-leguas");
    robot.attack("Coiote");
    robot.beRepaired(5);
    std::cout << "Teste attack sem vida ----------------------------------------------------------------" << std::endl;
    robot.takeDamage(20);
    robot.attack("Pernalonga");
    robot.beRepaired(3);

    return 0;
}