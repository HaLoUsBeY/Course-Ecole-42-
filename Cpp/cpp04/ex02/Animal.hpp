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
        virtual ~Animal();

        // BÜYÜ BURADA: "= 0" ekleyerek bunu "Pure Virtual" (Saf Sanal) yaptık.
        // Artık Animal sınıfı soyut (Abstract) bir sınıftır ve tek başına yaratılamaz!
        virtual void makeSound() const = 0; 
        
        std::string getType() const;
};

#endif