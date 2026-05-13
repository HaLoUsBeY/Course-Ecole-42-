#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    //Subject
    const Animal* j = new Dog();
    const Animal* i = new Cat();
    delete j; // should not create a leak
    delete i;
    
    std::cout << "===== ARRAY TEST =====" << std::endl;
    const int array_size = 4;
    Animal* animals[array_size];

    for (int i = 0; i < array_size; i++)
    {
        if (i < array_size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }
    std::cout << "\n--- Animals Sound ---" << std::endl;
    for (int i = 0; i < array_size; i++)
        animals[i]->makeSound();

    std::cout << "\n--- Memory Leak Check ---" << std::endl;
    for (int i = 0; i < array_size; i++)
        delete animals[i]; // virtual ~Animal()

    return 0;
}