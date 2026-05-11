#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal
{
    protected:
        std::string _type;

    public:
        Animal();
        Animal(std::string type);
        Animal(const Animal &src);
        Animal &operator=(const Animal &rhs);
        // Çok Önemli: Kalıtım alınan temel sınıfların yıkıcıları DAİMA virtual olmalıdır!
        virtual ~Animal();

        // BÜYÜ BURADA: virtual kelimesi sayesinde asıl objenin fonksiyonu çalışır!
        virtual void makeSound() const;
        std::string getType() const;
};

#endif