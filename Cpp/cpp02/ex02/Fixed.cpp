#include "Fixed.hpp"

// --- Constructors & Destructor ---
Fixed::Fixed() : _rawBits(0)
{
    std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const int n)
{
    std::cout << "Int constructor called" << std::endl;
    this->_rawBits = n << _fractionalBits;
}

Fixed::Fixed(const float f)
{
    std::cout << "Float constructor called" << std::endl;
    this->_rawBits = (int)roundf(f * (1 << _fractionalBits));
}

Fixed::Fixed(const Fixed& src)
{
    std::cout << "Copy constructor called" << std::endl;
    *this = src;
}

Fixed& Fixed::operator=(const Fixed& rhs)
{
    std::cout << "Copy assignment operator called" << std::endl;
    if (this != &rhs)
        this->_rawBits = rhs.getRawBits();
    return *this;
}

Fixed::~Fixed()
{
    std::cout << "Destructor called" << std::endl;
}

// --- Getter, Setter & Converters (Ex01) ---
int Fixed::getRawBits(void) const
{
    return this->_rawBits;
}

void Fixed::setRawBits(int const raw)
{
    this->_rawBits = raw;
}

float Fixed::toFloat(void) const
{
    return (float)this->_rawBits / (1 << _fractionalBits);
}

int Fixed::toInt(void) const
{
    return this->_rawBits >> _fractionalBits;
}

// --- Output Operator ---
std::ostream& operator<<(std::ostream& out, const Fixed& rhs)
{
    out << rhs.toFloat();
    return out;
}

// ==========================================
//          EX02 OPERATOR OVERLOADING
// ==========================================

// --- Comparison Operators ---
bool Fixed::operator>(const Fixed& rhs) const
{
    return this->getRawBits() > rhs.getRawBits();//is large
}

bool Fixed::operator<(const Fixed& rhs) const
{
    return this->getRawBits() < rhs.getRawBits();//is small
}

bool Fixed::operator>=(const Fixed& rhs) const
{
    return this->getRawBits() >= rhs.getRawBits();//large and equals   
}

bool Fixed::operator<=(const Fixed& rhs) const
{
    return this->getRawBits() <= rhs.getRawBits();//small and equals
}

bool Fixed::operator==(const Fixed& rhs) const
{
    return this->getRawBits() == rhs.getRawBits();//equals
}

bool Fixed::operator!=(const Fixed& rhs) const
{
    return this->getRawBits() != rhs.getRawBits();//not equals
}

// --- Arithmetic Operators ---
Fixed Fixed::operator+(const Fixed& rhs) const
{
    return Fixed(this->toFloat() + rhs.toFloat());
}

Fixed Fixed::operator-(const Fixed& rhs) const
{
    return Fixed(this->toFloat() - rhs.toFloat());
}

Fixed Fixed::operator*(const Fixed& rhs) const
{
    return Fixed(this->toFloat() * rhs.toFloat());
}

Fixed Fixed::operator/(const Fixed& rhs) const
{
    return Fixed(this->toFloat() / rhs.toFloat());
}

// --- Increment / Decrement Operators ---
// Prefix (++a)
Fixed& Fixed::operator++(void)//++a = printf(a+1) result -> a = a + 1
{
    this->_rawBits++;
    return *this;
}

// Postfix (a++) Dummy Parameter
Fixed Fixed::operator++(int)//a++ = printf(a) result -> a = a + 1
{
    Fixed tmp(*this);
    this->_rawBits++;
    return tmp;
}

// Prefix (--a)
Fixed& Fixed::operator--(void)
{
    this->_rawBits--;
    return *this;
}

// Postfix (a--) Dummy Parameter
Fixed Fixed::operator--(int)
{
    Fixed tmp(*this);
    this->_rawBits--;
    return tmp;
}

// --- Min / Max Functions ---
Fixed& Fixed::min(Fixed& a, Fixed& b)
{
    if (a < b)
        return a;
    return b;
}

const Fixed& Fixed::min(const Fixed& a, const Fixed& b)
{
    if (a < b)
        return a;
    return b;
}

Fixed& Fixed::max(Fixed& a, Fixed& b)
{
    if (a > b)
        return a;
    return b;
}

const Fixed& Fixed::max(const Fixed& a, const Fixed& b)
{
    if (a > b)
        return a;
    return b;
}