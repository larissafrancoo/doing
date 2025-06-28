#include "Zombie.hpp"
#include <iostream>

int main() {
	int N = 5;
	Zombie* horde = zombieHorde(N, "Caio");
	if (horde) {
		for (int i = 0; i < N; i++) horde[i].announce();
		delete[] horde;
	}
/*
	if (horde) {
		std::cout << "ptr de horde: " << &horde << "\n" << std::endl;
		for (int i = 0; i < N; i++){
			std::cout << "index: " << i << std::endl;
		       	horde[i].announce();
			std::cout << "ptr: " << &horde[i - 1] << "\n" << std::endl;
		}
		delete[] horde;
	}
*/

	return 0;
}
