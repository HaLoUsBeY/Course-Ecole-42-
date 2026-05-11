#include "Fixed.hpp"

//Default Constructor
Fixed::Fixed() : _rawBits(0)
{
	std::cout << "Default constructor called" << std::endl;
}

//Copy Constructor 
Fixed::Fixed(const Fixed& src)
{
	std::cout << "Copy constructor called" << std::endl;
	*this = src; // (operator=) b = a
}

// Copy Assignment Operator c = b = a;
Fixed& Fixed::operator=(const Fixed& rhs)//this->operator=(src);
{
	std::cout << "Copy assignment operator called" << std::endl;
	// (a = a;) = X
	if (this != &rhs)
		this->_rawBits = rhs.getRawBits();// self-assignment
	return *this;//c = b = a --> b = a --> c = &b
}

//Destructor
Fixed::~Fixed()
{
	std::cout << "Destructor called" << std::endl;
}

// --- Getter and Setter ---

int Fixed::getRawBits(void) const
{
	std::cout << "getRawBits member function called" << std::endl;
	return this->_rawBits;
}

void Fixed::setRawBits(int const raw)
{
	this->_rawBits = raw;
}