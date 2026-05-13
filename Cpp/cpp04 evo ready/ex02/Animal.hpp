#ifndef ANIMAL_HPP
#define ANIMAL_HPP

#include <iostream>
#include <string>

class Animal//abstract class
{
    protected:
        std::string _type;

    public:
        Animal();
        Animal(std::string type);
        Animal(const Animal &src);
        Animal &operator=(const Animal &rhs);
        virtual ~Animal();

        virtual void makeSound() const = 0;  //pure virtual
        std::string getType() const;
};

#endif