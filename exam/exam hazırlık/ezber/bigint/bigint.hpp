#ifndef BIGINT_HPP
#define BIGINT_HPP

#include <string>
#include <iostream>

class bigint
{
	private:
		std::string _n; // en anlamli basamak basta: 1337 -> "1337"

	public:
		bigint();
		bigint(unsigned int x);
		bigint(const bigint& o);
		bigint& operator=(const bigint& o);
		~bigint();

		bigint  operator+(const bigint& o) const;
		bigint& operator+=(const bigint& o);
		bigint& operator++();
		bigint  operator++(int);

		bigint  operator<<(unsigned int n) const;
		bigint  operator>>(unsigned int n) const;
		bigint& operator<<=(unsigned int n);
		bigint& operator>>=(unsigned int n);
		bigint  operator<<(const bigint& n) const;
		bigint  operator>>(const bigint& n) const;
		bigint& operator<<=(const bigint& n);
		bigint& operator>>=(const bigint& n);

		bool operator==(const bigint& o) const;
		bool operator!=(const bigint& o) const;
		bool operator<(const bigint& o) const;
		bool operator>(const bigint& o) const;
		bool operator<=(const bigint& o) const;
		bool operator>=(const bigint& o) const;

		const std::string& str() const;
};

std::ostream& operator<<(std::ostream& os, const bigint& b);

#endif
