#include "Animal.hpp"

Animal::Animal()
{
    this->type = "Animal Base Class";
    std::cout << "Animal default constructor called" << std::endl;
}
Animal::Animal(std::string type) : type(type)
{
    std::cout << "Animal constructor called" << std::endl;
}
Animal::Animal(const Animal &copy) : type(copy.type)
{
    std::cout << "Animal copy constructor called" << std::endl;
}
Animal &Animal::operator=(const Animal &copy)
{
    std::cout << "Animal copy assignment operator called" << std::endl;
    if (this != &copy)
        this->type = copy.type;
    return *this;
}
Animal::~Animal()
{
    std::cout << "Animal destructor called" << std::endl;
}
std::string Animal::getType() const
{
    return this->type;
}