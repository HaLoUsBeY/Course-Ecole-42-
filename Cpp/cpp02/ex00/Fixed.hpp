#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
	private:
		int                 _rawBits;//fixed point
		static const int    _fractionalBits = 8;//2^8

	public:
		// --- orthodox canonical form ---
		Fixed();                                //Default constructor
		Fixed(const Fixed& src);                //Copy constructor
		Fixed& operator=(const Fixed& rhs);    	//Copy assignment operator
		~Fixed();                              	//Destructor


		int     getRawBits(void) const;
		void    setRawBits(int const raw);
};

#endif