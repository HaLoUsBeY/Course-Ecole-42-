#include "Animal.hpp"

//Default Constructor
Animal::Animal() : _type("Unknown")
{
	std::cout << "Animal default constructor called" << std::endl;
}

//Parameter Constructor
Animal::Animal(std::string type) : _type(type)
{
	std::cout << "Animal constructor called" << std::endl;
}

//Copy Constructor
Animal::Animal(const Animal &other) : _type(other._type)
{
	std::cout << "Animal copy constructor called" << std::endl;
	*this = other;//shallow copy(default)
}

//Copy Assignment Operator (deep copy)
Animal &Animal::operator=(const Animal &other)
{
	if (this != &other)
		_type = other._type;
	std::cout << "Animal copy assignment operator called" << std::endl;
	return *this;
}

//destructor
Animal::~Animal()
{
	std::cout << "Animal destructor called" << std::endl;
}

//virtual trigger
void Animal::makeSound() const
{
	std::cout << "Animal makeSound" << std::endl;
}

//getter
std::string Animal::getType() const
{
	return (_type);
}