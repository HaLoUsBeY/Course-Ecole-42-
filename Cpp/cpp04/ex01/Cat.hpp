#ifndef CAT_HPP
#define CAT_HPP

#include "Animal.hpp"
#include "Brain.hpp"

class Cat : public Animal
{
    private:
        Brain* _brain; // Kedinin özel beyni (Pointer)

    public:
        Cat();
        Cat(const Cat &src);
        Cat &operator=(const Cat &rhs);
        ~Cat();

        virtual void makeSound() const;
};

#endif