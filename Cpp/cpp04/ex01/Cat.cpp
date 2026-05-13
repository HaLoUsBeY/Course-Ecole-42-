#include "Cat.hpp"

//default constructor
Cat::Cat() : Animal()
{
    this->_type = "Cat";
    this->_brain = new Brain();
    std::cout << "Cat Default Constructor called" << std::endl;
}

//copy constructor
Cat::Cat(const Cat &src) : Animal(src)
{
    std::cout << "Cat Copy Constructor called" << std::endl;
    this->_brain = new Brain(*(src._brain));//deep copy
}

//copy assssingment operator
Cat &Cat::operator=(const Cat &rhs)
{
    std::cout << "Cat Assignment Operator called" << std::endl;
    if (this != &rhs)
    {
        this->_type = rhs._type;
        if (this->_brain)
            delete this->_brain;
        this->_brain = new Brain(*(rhs._brain));
    }
    return *this;
}

//destructor
Cat::~Cat()
{
    delete this->_brain;
    std::cout << "Cat Destructor called" << std::endl;
}

void Cat::makeSound() const
{
    std::cout << "Meow! Meow!" << std::endl;
}