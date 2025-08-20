#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main() {
    const int N = 4;
    Animal* animals[N];

    for (int i = 0; i < N; ++i) {
        if (i < N / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    Dog original;
    original.setIdea(0, "Chase the mailman");

    Dog copy = original;
    copy.setIdea(0, "Sleep all day");

    std::cout << "Original idea: " << original.getIdea(0) << std::endl;
    std::cout << "Copy idea: " << copy.getIdea(0) << std::endl;

    for (int i = 0; i < N; ++i)
        delete animals[i];

    return 0;
}