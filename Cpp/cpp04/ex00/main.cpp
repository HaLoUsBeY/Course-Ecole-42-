#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"
#include "WrongAnimal.hpp"
#include "WrongCat.hpp"

int main()
{
    std::cout << "===== 1. DOĞRU POLİMORFİZM (VIRTUAL VAR) =====" << std::endl;
    const Animal* meta = new Animal();
    const Animal* j = new Dog();//((Dog*)j)->kemik_gom(); ->Downcasting (Aşağı Çevrim)
    const Animal* i = new Cat();

    std::cout << "\nTürler:" << std::endl;
    std::cout << "j'nin türü: " << j->getType() << std::endl;
    std::cout << "i'nin türü: " << i->getType() << std::endl;

    std::cout << "\nSes Çıkarma:" << std::endl;
    i->makeSound(); // virtual olduğu için KEDİ sesi çıkarır!
    j->makeSound(); // virtual olduğu için KÖPEK sesi çıkarır!
    meta->makeSound();

    std::cout << "\nYıkıcılar (Destructors):" << std::endl;
    delete i;
    delete j;
    delete meta;

    std::cout << "\n\n===== 2. YANLIŞ POLİMORFİZM (VIRTUAL YOK) =====" << std::endl;
    const WrongAnimal* wrong_meta = new WrongAnimal();
    const WrongAnimal* wrong_i = new WrongCat();

    std::cout << "\nTürler:" << std::endl;
    std::cout << "wrong_i'nin türü: " << wrong_i->getType() << std::endl;

    std::cout << "\nSes Çıkarma:" << std::endl;
    // DİKKAT! Burada asıl obje Kedi olmasına rağmen virtual olmadığı için WrongAnimal sesi çıkaracak!
    wrong_i->makeSound(); 
    wrong_meta->makeSound();

    std::cout << "\nYıkıcılar (Destructors):" << std::endl;
    delete wrong_i;
    delete wrong_meta;

    return 0;
}




/*
// 3 kapasiteli tek bir "Animal Pointer" dizisi açıyoruz
Animal* hayvanat_bahcesi[3];

// Hepsini AYNI dizi üzerinden yönetiyoruz!
hayvanat_bahcesi[0] = new Animal(); // Düz hayvan
hayvanat_bahcesi[1] = new Dog();    // Köpek
hayvanat_bahcesi[2] = new Cat();    // Kedi

// Döngüyle tek seferde hepsini seslendiriyoruz
for (int k = 0; k < 3; k++) {
    hayvanat_bahcesi[k]->makeSound(); 
    // virtual kelimesi sayesinde 1. sıradaki havlar, 2. sıradaki miyavlar!
}
*/