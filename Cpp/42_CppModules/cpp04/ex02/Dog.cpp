#include "Dog.hpp"

Dog::Dog()
{
    this->type = "Dog Class";
    this->brain = new Brain();
    std::cout << "Dog default constructor called" << std::endl;
}
Dog::Dog(std::string type) : Animal(type)
{
    this->brain = new Brain();
    std::cout << "Dog constructor called" << std::endl;
}
Dog::Dog(const Dog &copy) : Animal(copy.type)
{
    this->brain = new Brain(*copy.brain);
    std::cout << "Dog copy constructor called" << std::endl;
}
Dog &Dog::operator=(const Dog &copy)
{
    std::cout << "Dog copy assignment operator called" << std::endl;
    if (this != &copy)
    {
        this->type = copy.type;
        delete this->brain;
        this->brain = new Brain(*copy.brain);
    }
    return *this;
}
Dog::~Dog()
{
    delete this->brain;
    std::cout << "Dog destructor called" << std::endl;
}
void Dog::makeSound() const
{
    std::cout << "Dog sound" << std::endl;
}