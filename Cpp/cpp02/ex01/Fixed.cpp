#include "Fixed.hpp"

//Default Constructor
Fixed::Fixed() : _rawBits(0)
{
    std::cout << "Default constructor called" << std::endl;
}

// Int parameter Constructor
// read machine fixed-point format
Fixed::Fixed(const int n)//b = 10 -> rawbits = 10 * 256 = 2560
{
    std::cout << "Int constructor called" << std::endl;
    this->_rawBits = n << _fractionalBits;
}

// Float parameter Constructor
// read machine fixed-point format
Fixed::Fixed(const float f)
{
    std::cout << "Float constructor called" << std::endl;
    this->_rawBits = (int)roundf(f * (1 << _fractionalBits)); //static cast 65 -> 'A;
}

//Copy Constructor
Fixed::Fixed(const Fixed& src)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

//Copy Assignment Operator
Fixed& Fixed::operator=(const Fixed& rhs)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
        this->_rawBits = rhs.getRawBits();
    return *this;
}

//Destructor
Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

// --- Getter and Setter ---
int Fixed::getRawBits(void) const
{
    return this->_rawBits;
}

void Fixed::setRawBits(int const raw)
{
    this->_rawBits = raw;
}

// --- to functions ---
// human read
float Fixed::toFloat(void) const
{
    return (float)this->_rawBits / (1 << _fractionalBits);////static cast 65 -> 'A';
}

//human read
int Fixed::toInt(void) const // b = rawbits / fractionalBits(8) = 2560 / 256 = 10
{
    return this->_rawBits >> _fractionalBits;
}

// Operator Overloading
std::ostream& operator<<(std::ostream& out, const Fixed& rhs)
{
    out << rhs.toFloat();
    return out;
}