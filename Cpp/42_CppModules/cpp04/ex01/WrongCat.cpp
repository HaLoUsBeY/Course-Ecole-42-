#include "WrongCat.hpp"

WrongCat::WrongCat()
{
    this->type = "WrongCat";
    std::cout << "WrongCat default constructor called" << std::endl;
}
WrongCat::WrongCat(std::string type) : WrongAnimal(type)
{
    std::cout << "WrongCat constructor called" << std::endl;
}
WrongCat::WrongCat(const WrongCat &copy) : WrongAnimal(copy.type)
{
    std::cout << "WrongCat copy constructor called" << std::endl;
}
WrongCat &WrongCat::operator=(const WrongCat &copy)
{
    std::cout << "WrongCat copy assignment operator called" << std::endl;
    if (this != &copy)
        this->type = copy.type;
    return *this;
}
WrongCat::~WrongCat()
{
    std::cout << "WrongCat destructor called" << std::endl;
}
void WrongCat::makeSound() const
{
    std::cout << "WrongCat sound" << std::endl;
}