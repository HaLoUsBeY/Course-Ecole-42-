#include "WrongAnimal.hpp"

WrongAnimal::WrongAnimal() : _type("Wrong_Default")
{
    std::cout << "WrongAnimal Default Constructor called" << std::endl;
}

WrongAnimal::WrongAnimal(std::string type) : _type(type)
{
    std::cout << "WrongAnimal Parameterized Constructor called" << std::endl;
}
//static binding
WrongAnimal::WrongAnimal(const WrongAnimal &src)
{
    std::cout << "WrongAnimal Copy Constructor called" << std::endl;
    *this = src;
}

WrongAnimal &WrongAnimal::operator=(const WrongAnimal &rhs)
{
    std::cout << "WrongAnimal Assignment Operator called" << std::endl;
    if (this != &rhs) {
        this->_type = rhs._type;
    }
    return *this;
}

WrongAnimal::~WrongAnimal()
{
    std::cout << "WrongAnimal Destructor called" << std::endl;
}

void WrongAnimal::makeSound() const
{
    std::cout << "* WRONG Animal Noise! *" << std::endl;
}

std::string WrongAnimal::getType() const
{
    return this->_type;
}