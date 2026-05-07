#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    // Subject test
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    delete j; // should not create a leak
    delete i;

    std::cout << std::endl;

    // Array test
    const int size = 4;
    Animal* animals[size];
    
    for (int idx = 0; idx < size / 2; idx++)
        animals[idx] = new Dog();
    
    for (int idx = size / 2; idx < size; idx++)
        animals[idx] = new Cat();
    
    for (int idx = 0; idx < size; idx++)
        delete animals[idx];

    std::cout << std::endl;

    // Deep copy test
    Dog basic;
    {
        Dog tmp = basic;
    }

    return 0;
}
