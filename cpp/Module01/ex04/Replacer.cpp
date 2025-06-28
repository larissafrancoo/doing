#include "Replacer.hpp"
#include <iostream>
#include <fstream>

Replacer::Replacer(const std::string &filename, const std::string &s1, const std::string &s2) : filename(filename), s1(s1), s2(s2) {}
Replacer::~Replacer() {}

std::string Replacer::replaceLine(std::string &line) {
	std::string ret;
	size_t pos = 0; //o que é um size_t e o que é um 'pos'?
	size_t found;

	while ((found = line.find(s1, pos)) != std::string::npos/*o que é esse parâmetro?*/) {
		ret += line.substr(pos, found - pos);
		ret += s2;
		pos = found + s1.length();
	}
	ret += line.substr(pos);
	return ret;
}

int Replacer::sei_la() {
	std::ifstream file(filename.c_str()/*o que é 'c_str'?*/);
	if (!file.is_open()) {
		std::cerr << "Error to open file." << std::endl;
		return false;
	}

	std::ofstream fole((filename + ".replace").c_str());//o que é o fole? e como ele se encaixa no c_str?
	if (!fole.is_open()) {
		std::cerr << "Error to create replace file." << std::endl;
		file.close();
		return false;
	}

	std::string line;
	while (std::getline(file, line)) {
		std::cout << line << std::endl;
		fole << replaceLine(line) << std::endl;
	}

	file.close();
	fole.close();

	return true;
}
