#include "Dog.hpp"

Dog::Dog()
{
    this->type = "Dog Class";
    std::cout << "Dog default constructor called" << std::endl;
}
Dog::Dog(std::string type) : Animal(type)
{
    std::cout << "Dog constructor called" << std::endl;
}
Dog::Dog(const Dog &copy) : Animal(copy.type)
{
    std::cout << "Dog copy constructor called" << std::endl;
}
Dog &Dog::operator=(const Dog &copy)
{
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this != &copy)
        this->type = copy.type;
    return *this;
}
Dog::~Dog()
{
    std::cout << "Dog destructor called" << std::endl;
}
void Dog::makeSound() const
{
    std::cout << "Dog sound" << std::endl;
}