#include "bigint.hpp"
#include <sstream>
#include <cstdlib>

/* 1) Kurucu: sayiyi stringe cevir */
bigint::bigint(size_t x)
{
	std::ostringstream o;
	o << x;
	sayi = o.str();
}

/* 2) Toplama: sagdan sola, elde ile; her basamagi basa ekle */
bigint bigint::operator+(const bigint& b) const
{
	std::string r;
	int i = sayi.size() - 1;
	int j = b.sayi.size() - 1;
	int elde = 0;

	while (i >= 0 || j >= 0 || elde)
	{
		int t = elde;
		if (i >= 0)
			t += sayi[i--] - '0';
		if (j >= 0)
			t += b.sayi[j--] - '0';
		r = (char)('0' + t % 10) + r;
		elde = t / 10;
	}
	bigint s;
	s.sayi = r;
	return s;
}

bigint& bigint::operator+=(const bigint& b) { *this = *this + b; return *this; }
bigint& bigint::operator++() { *this = *this + 1; return *this; }
bigint  bigint::operator++(int) { bigint eski = *this; ++(*this); return eski; }

/* 3) Kaydirma: << sona '0' ekle, >> sondan sil */
bigint bigint::operator<<(const bigint& b) const
{
	bigint s = *this;
	if (sayi != "0")
		s.sayi += std::string(std::atoi(b.sayi.c_str()), '0');
	return s;
}

bigint bigint::operator>>(const bigint& b) const
{
	bigint s = *this;
	size_t k = std::atoi(b.sayi.c_str());
	if (k >= sayi.size())
		s.sayi = "0";
	else
		s.sayi = sayi.substr(0, sayi.size() - k);
	return s;
}

bigint& bigint::operator<<=(const bigint& b) { *this = *this << b; return *this; }
bigint& bigint::operator>>=(const bigint& b) { *this = *this >> b; return *this; }

/* 4) Karsilastirma: once uzunluk, esitse string; gerisi < ve == den */
bool bigint::operator<(const bigint& b) const
{
	if (sayi.size() != b.sayi.size())
		return sayi.size() < b.sayi.size();
	return sayi < b.sayi;
}
bool bigint::operator>(const bigint& b) const  { return b < *this; }
bool bigint::operator<=(const bigint& b) const { return !(b < *this); }
bool bigint::operator>=(const bigint& b) const { return !(*this < b); }
bool bigint::operator==(const bigint& b) const { return sayi == b.sayi; }
bool bigint::operator!=(const bigint& b) const { return !(*this == b); }

/* 5) Yazdirma */
std::ostream& operator<<(std::ostream& os, const bigint& b)
{
	os << b.sayi;
	return os;
}
