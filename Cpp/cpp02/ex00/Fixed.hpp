#ifndef FIXED_HPP
#define FIXED_HPP

#include <iostream>

class Fixed
{
    private:
        int                 _rawBits; // Sayının ham halini tutacak
        static const int    _fractionalBits = 8; // Her zaman 8 kalacak sabit

    public:
        // --- Ortodoks Kanonik Form ---
        Fixed();                                // 1. Default constructor
        Fixed(const Fixed& src);                // 2. Copy constructor
        Fixed& operator=(const Fixed& rhs);     // 3. Copy assignment operator
        ~Fixed();                               // 4. Destructor

        // --- Sınıfa Özel Fonksiyonlar ---
        int     getRawBits(void) const;
        void    setRawBits(int const raw);
};

#endif