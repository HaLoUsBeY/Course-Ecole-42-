#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class bigint
{
public:
	std::string sayi;              // 1337 -> "1337"

	bigint(size_t x = 0);          // bigint c; ve bigint a(42); ikisi de bu

	bigint  operator+(const bigint& b) const;
	bigint& operator+=(const bigint& b);
	bigint& operator++();
	bigint  operator++(int);

	bigint  operator<<(const bigint& b) const;
	bigint  operator>>(const bigint& b) const;
	bigint& operator<<=(const bigint& b);
	bigint& operator>>=(const bigint& b);

	bool operator<(const bigint& b) const;
	bool operator>(const bigint& b) const;
	bool operator<=(const bigint& b) const;
	bool operator>=(const bigint& b) const;
	bool operator==(const bigint& b) const;
	bool operator!=(const bigint& b) const;
};

std::ostream& operator<<(std::ostream& os, const bigint& b);

#endif
