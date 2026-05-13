#include "Cat.hpp"

//Default Constructor
Cat::Cat() : Animal("Cat")
{
    std::cout << "Cat Default Constructor called" << std::endl;
}

//Parameter Constructor
Cat::Cat(const Cat &src) : Animal(src)
{
    std::cout << "Cat Copy Constructor called" << std::endl;
    *this = src;
}

//Copya Assignment Operator
Cat &Cat::operator=(const Cat &rhs)
{
    std::cout << "Cat Assignment Operator called" << std::endl;
    if (this != &rhs) {
        this->_type = rhs._type;
    }
    return *this;
}

//Destructor
Cat::~Cat()
{
    std::cout << "Cat Destructor called" << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "Meow! Meow! Purr..." << std::endl;
}