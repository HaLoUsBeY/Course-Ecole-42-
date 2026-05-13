#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    {
        std::cout << "-----Animal (True Polymorphism)-----" << std::endl;
        const Animal* meta = new Animal();
        const Animal* j = new Dog();
        const Animal* i = new Cat();
        std::cout << meta->getType() << " " << std::endl;
        std::cout << j->getType() << " " << std::endl;
        std::cout << i->getType() << " " << std::endl;
        i->makeSound();
        j->makeSound();
        meta->makeSound();
        delete meta;
        delete i;
        delete j;
    }
    {
        std::cout << "-----Wrong Animal (False Polymorphism)-----" << std::endl;
        const WrongAnimal* meta = new WrongAnimal();
        const WrongAnimal* k = new WrongCat();
        std::cout << meta->getType() << " " << std::endl;
        std::cout << k->getType() << " " << std::endl;
        k->makeSound();
        meta->makeSound();
        delete meta;
        delete k;
    }
    return 0;
}
