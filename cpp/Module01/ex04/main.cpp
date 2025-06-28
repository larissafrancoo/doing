#include "Replacer.hpp"
#include <iostream>

int main(int ac, char **av) {
	if (ac != 4) {
		std::cerr << "Parameters: ./replace <file> <s1> <s2>" << std::endl;
		return (1);
	}

	Replacer fReplacer(av[1], av[2], av[3]);
	if (!fReplacer.sei_la())
		return (1);
	return (0);
}
