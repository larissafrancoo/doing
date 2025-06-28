#include "Zombie.hpp"

int main() {
	Zombie* hZ = newZombie("Zombie on heap");
	hZ->announce();
	delete hZ;

	randomChump("Zombie on stack");
	return 0;
}
