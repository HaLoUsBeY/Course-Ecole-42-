#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <iostream>
#include <string>


class bigint
{
    public:
        std::string sayi;

        bigint(size_t x = 0);
        bigint operator+(const bigint& b) const;
        bigint& operator+=(const bigint& b);
        bigint& operator++();
        bigint operator++(int);
        bigint& operator<<=(const bigint& b);
        bigint& operator>>=(const bigint& b);
        bigint operator<<(const bigint& b) const;
        bigint operator>>(const bigint& b) const;
        bool operator<(const bigint& b) const;
        bool operator>(const bigint& b) const ;       
        bool operator<=(const bigint& b) const;
        bool operator>=(const bigint& b) const;
        bool operator==(const bigint& b) const;
        bool operator!=(const bigint& b) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& b);

#endif