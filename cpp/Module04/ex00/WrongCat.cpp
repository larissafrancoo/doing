#include "WrongCat.hpp"

WrongCat::WrongCat() {
    type = "WrongCat";
    std::cout << "[WrongCat] I was born" << std::endl;
}

WrongCat::~WrongCat() {
    std::cout << "[WrongCat] I died" << std::endl;
}

void WrongCat::makeSound() const {
    std::cout << "[WrongCat] Meeeow??" << std::endl;
}