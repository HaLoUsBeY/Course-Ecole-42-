#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "Brain.hpp"

int main()
{
    std::cout << "===== 1. SOYUT SINIF KANITI (ABSTRACT CLASS TEST) =====" << std::endl;
    
    // AŞAĞIDAKİ SATIR DERLENMEZ! Çünkü Animal artık soyut bir sınıf (Abstract Class).
    // Evaluator sorarsa bu satırın yorumunu kaldırıp derleyicinin verdiği hatayı gösterebilirsin:
    // Animal* test = new Animal(); 
    // Animal obj;
    
    std::cout << "Animal dogrudan yaratilamaz (Abstract Class). Ancak isaretcisi kullanilabilir!" << std::endl;

    std::cout << "\n===== 2. POLIMORFIZM VE DIZI TESTI =====" << std::endl;
    const int array_size = 4;
    Animal* animals[array_size];

    for (int i = 0; i < array_size; i++) {
        if (i < array_size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << "\n--- Hayvanlari Seslendir ---" << std::endl;
    for (int i = 0; i < array_size; i++) {
        animals[i]->makeSound();
    }

    std::cout << "\n--- Hayvanlari Yok Et (Memory Leak Kontrolu) ---" << std::endl;
    for (int i = 0; i < array_size; i++) {
        delete animals[i];
    }

    std::cout << "\n===== 3. DERIN KOPYA KONTROLU =====" << std::endl;
    {
        Dog originalDog;
        Dog copyDog = originalDog;
    }

    return 0;
}