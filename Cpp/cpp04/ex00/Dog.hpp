#ifndef DOG_HPP
#define DOG_HPP

#include "Animal.hpp"

class Dog : public Animal
{
    public:
        Dog();
        Dog(const Dog &src);
        Dog &operator=(const Dog &rhs);
        ~Dog();

        // override keyword'ü C++11'dir, biz C++98'de olduğumuz için sadece virtual yazıyoruz
        virtual void makeSound() const;
};

#endif