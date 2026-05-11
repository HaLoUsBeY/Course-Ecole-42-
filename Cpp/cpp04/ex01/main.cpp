#include "Animal.hpp"
#include "Dog.hpp"
#include "Cat.hpp"

int main()
{
    std::cout << "===== 1. DİZİ TESTİ (ARRAY TEST) =====" << std::endl;
    const int array_size = 4;
    Animal* animals[array_size];

    // Yarısını Köpek, yarısını Kedi yap
    for (int i = 0; i < array_size; i++) {
        if (i < array_size / 2)
            animals[i] = new Dog();
        else
            animals[i] = new Cat();
    }

    std::cout << "\n--- Hayvanları Seslendir ---" << std::endl;
    for (int i = 0; i < array_size; i++) {
        animals[i]->makeSound();
    }

    std::cout << "\n--- Hayvanları Yok Et (Memory Leak Kontrolü) ---" << std::endl;
    for (int i = 0; i < array_size; i++) {
        delete animals[i]; // virtual ~Animal() sayesinde Cat ve Dog destructor'ları çalışacak!
    }

    std::cout << "\n===== 2. DERİN KOPYA TESTİ (DEEP COPY TEST) =====" << std::endl;
    {
        Dog originalDog; // Orijinal köpek doğar
        std::cout << "\n--- Kopyalama İşlemi ---" << std::endl;
        Dog copyDog = originalDog; // Kopya köpek doğar (Farklı beyni olmalı)
        
        std::cout << "\n--- Scope'tan Çıkış (Yıkıcılar Çağrılıyor) ---" << std::endl;
        // Eğer Shallow Copy (Sığ Kopya) yapsaydık, burada program çökerdi (Double free).
        // Çünkü iki köpek aynı beyni silmeye çalışırdı. Biz Deep Copy yaptığımız için sorunsuz kapanacak.
    }

    return 0;
}