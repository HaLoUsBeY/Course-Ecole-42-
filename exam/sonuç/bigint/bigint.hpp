#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>
#include <cstdlib>
#include <sstream>

class bigint
{
    public:
        std::string sayi;

        bigint::bigint(size_t x = 0);

        bigint bigint::operator+(const bigint& b) const;
        bigint& bigint::operator+=(const bigint& b)
        bigint& bigint::operator++();
        bigint bigint::operator++(int);

        bigint bigint::operator<<(const bigint& b) const;
        bigint bigint::operator>>(const bigint& b) const;

        bigint& bigint::operator<<=(const bigint& b) ;
        bigint& bigint::operator>>=(const bigint& b) ;

        bool bigint::operator<(const bigint& b) const;
        bool bigint::operator>(const bigint& b) const ;
        bool bigint::operator<=(const bigint& b) const ;
        bool bigint::operator>=(const bigint& b) const ;
        bool bigint::operator==(const bigint& b) const;
        bool bigint::operator!=(const bigint& b) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& b);

#endif