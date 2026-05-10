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
        // --- Orthodox Canonical Form ---
        Fixed();
        Fixed(const Fixed& src);
        Fixed& operator=(const Fixed& rhs);
        ~Fixed();

        // --- Constructors and Parameter ---
        Fixed(const int n);
        Fixed(const float f);

        // --- Getters, Setters & Converters ---
        int     getRawBits(void) const;
        void    setRawBits(int const raw);
        float   toFloat(void) const;
        int     toInt(void) const;

        // --- Comparison Operators (Ex02) ---
        bool    operator>(const Fixed& rhs) const;
        bool    operator<(const Fixed& rhs) const;
        bool    operator>=(const Fixed& rhs) const;
        bool    operator<=(const Fixed& rhs) const;
        bool    operator==(const Fixed& rhs) const;
        bool    operator!=(const Fixed& rhs) const;

        // --- Arithmetic Operators (Ex02) ---
        Fixed   operator+(const Fixed& rhs) const;
        Fixed   operator-(const Fixed& rhs) const;
        Fixed   operator*(const Fixed& rhs) const;
        Fixed   operator/(const Fixed& rhs) const;

        // --- Increment / Decrement Operators (Ex02) ---
        Fixed&  operator++(void); // Prefix (++a)
        Fixed   operator++(int);  // Postfix (a++)
        Fixed&  operator--(void); // Prefix (--a)
        Fixed   operator--(int);  // Postfix (a--)

        // --- Min / Max Functions (Ex02) ---
        static Fixed& min(Fixed& a, Fixed& b);
        static const Fixed& min(const Fixed& a, const Fixed& b);
        static Fixed& max(Fixed& a, Fixed& b);
        static const Fixed& max(const Fixed& a, const Fixed& b);
};

// --- Output Operator ---
std::ostream& operator<<(std::ostream& out, const Fixed& rhs);

#endif