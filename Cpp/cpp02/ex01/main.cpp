#include "Fixed.hpp"
int main(void)
{
	Fixed a; //default constructor
	Fixed const b(10);//int parameter consturctor
	Fixed const c(42.42f);//float parameter constructor
	Fixed const d(b);//copy constructor -> copy assingment operator
	a = Fixed(1234.4321f); //float parameter constructor -> copy assignment operator -> destructor called
	std::cout << "a is " << a << std::endl;
	std::cout << "b is " << b << std::endl;
	std::cout << "c is " << c << std::endl;
	std::cout << "d is " << d << std::endl;
	std::cout << "a is " << a.toInt() << " as integer" << std::endl;
	std::cout << "b is " << b.toInt() << " as integer" << std::endl;
	std::cout << "c is " << c.toInt() << " as integer" << std::endl;
	std::cout << "d is " << d.toInt() << " as integer" << std::endl;
	return 0;
}