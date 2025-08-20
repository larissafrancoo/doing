#include "WrongAnimal.hpp"
#include "WrongCat.hpp"
#include <iostream>

int main() {
    std::cout << "--- Wrong example ---" << std::endl;

    const WrongAnimal* wrong = new WrongCat();

    std::cout << wrong->getType() << std::endl;
    wrong->makeSound();

    delete wrong;
    return 0;
}