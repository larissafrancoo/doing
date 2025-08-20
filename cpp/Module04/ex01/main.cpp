#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const int N = 4;
    Animal* animals[N];
    
    for (int i = 0; i < N; ++i) {
        if (i < N / 2) {
            animals[i] = new Dog();
            std::cout << "@@@@@@@@@@@@@@@@@@@@@@@" << std::endl;
        }
        else {
            animals[i] = new Cat();
            std::cout << "#########################" << std::endl;
        }
    }

    Dog original;
    original.setIdea(0, "Buy a pizza");

    Dog copy = original;
    copy.setIdea(0, "Sleep all day");

    std::cout << "Original idea: " << original.getIdea(0) << std::endl;
    std::cout << "Copy idea: " << copy.getIdea(0) << std::endl;

    for (int i = 0; i < N; ++i)
        delete animals[i];

    return 0;
}