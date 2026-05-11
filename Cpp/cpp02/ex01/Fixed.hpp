#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>
#include <cmath> // roundf

class Fixed
{
    private:
        int                 _rawBits;
        static const int    _fractionalBits = 8;

    public:
        // --- orthodox canonical form ---
        Fixed();                                 //Default constructor
        Fixed(const Fixed& src);                 //Copy constructor
        Fixed& operator=(const Fixed& rhs);      //Copy assignment operator
        ~Fixed();                                //Destructor

        // --- constructer and parameter ---
        Fixed(const int n);
        Fixed(const float f);

        int     getRawBits(void) const;
        void    setRawBits(int const raw);
        float   toFloat(void) const;
        int     toInt(void) const;
};

std::ostream& operator<<(std::ostream& out, const Fixed& rhs);

#endif