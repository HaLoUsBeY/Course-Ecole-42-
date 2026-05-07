#include "Cat.hpp"

Cat::Cat()
{
    this->type = "Cat Class";
    std::cout << "Cat default constructor called" << std::endl;
}
Cat::Cat(std::string type) : Animal(type)
{
    std::cout << "Cat constructor called" << std::endl;
}
Cat::Cat(const Cat &copy) : Animal(copy)
{
    std::cout << "Cat copy constructor called" << std::endl;
}
Cat &Cat::operator=(const Cat &copy)
{
    std::cout << "Cat copy assignment operator called" << std::endl;
    if (this != &copy)
        this->type = copy.type;
    return *this;
}
Cat::~Cat()
{
    std::cout << "Cat destructor called" << std::endl;
}
void Cat::makeSound() const
{
    std::cout << "Cat sound" << std::endl;
}