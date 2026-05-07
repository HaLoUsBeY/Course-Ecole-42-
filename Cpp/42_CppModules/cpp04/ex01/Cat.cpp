#include "Cat.hpp"

Cat::Cat()
{
    this->type = "Cat Class";
    this->brain = new Brain();
    std::cout << "Cat default constructor called" << std::endl;
}
Cat::Cat(std::string type) : Animal(type)
{
    this->brain = new Brain();
    std::cout << "Cat constructor called" << std::endl;
}
Cat::Cat(const Cat &copy) : Animal(copy)
{
    this->brain = new Brain(*copy.brain);
    std::cout << "Cat copy constructor called" << std::endl;
}
Cat &Cat::operator=(const Cat &copy)
{
    std::cout << "Cat copy assignment operator called" << std::endl;
    if (this != &copy)
    {
        this->type = copy.type;
        delete this->brain;
        this->brain = new Brain(*copy.brain);
    }
    return *this;
}
Cat::~Cat()
{
    delete this->brain;
    std::cout << "Cat destructor called" << std::endl;
}
void Cat::makeSound() const
{
    std::cout << "Cat sound" << std::endl;
}