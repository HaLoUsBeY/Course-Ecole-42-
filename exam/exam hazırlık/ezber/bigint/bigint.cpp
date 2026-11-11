#include "bigint.hpp"

/* ---------- 1) Orthodox Canonical Form ---------- */
bigint::bigint() : _n("0") {}

bigint::bigint(unsigned int x) : _n("")
{
	if (x == 0)
		_n = "0";
	while (x > 0)
	{
		_n.insert(_n.begin(), (char)('0' + x % 10));
		x /= 10;
	}
}

bigint::bigint(const bigint& o) : _n(o._n) {}

bigint& bigint::operator=(const bigint& o)
{
	if (this != &o)
		_n = o._n;
	return *this;
}

bigint::~bigint() {}

const std::string& bigint::str() const { return _n; }

/* ---------- 2) Toplama: ilkokul usulu, sagdan sola + elde ---------- */
bigint bigint::operator+(const bigint& o) const
{
	std::string r;
	int i = (int)_n.size() - 1;
	int j = (int)o._n.size() - 1;
	int carry = 0;

	while (i >= 0 || j >= 0 || carry)
	{
		int s = carry;
		if (i >= 0)
			s += _n[i--] - '0';
		if (j >= 0)
			s += o._n[j--] - '0';
		r.insert(r.begin(), (char)('0' + s % 10));
		carry = s / 10;
	}
	bigint res;
	res._n = r;
	return res;
}

bigint& bigint::operator+=(const bigint& o) { *this = *this + o; return *this; }
bigint& bigint::operator++() { *this = *this + bigint(1); return *this; }
bigint  bigint::operator++(int) { bigint tmp(*this); ++(*this); return tmp; }

/* ---------- 3) Basamak kaydirma: sona '0' ekle / sondan sil ---------- */
bigint bigint::operator<<(unsigned int n) const
{
	bigint r(*this);
	if (r._n != "0")
		r._n.append(n, '0');
	return r;
}

bigint bigint::operator>>(unsigned int n) const
{
	bigint r(*this);
	if (n >= r._n.size())
		r._n = "0";
	else
		r._n.erase(r._n.size() - n);
	return r;
}

bigint& bigint::operator<<=(unsigned int n) { *this = *this << n; return *this; }
bigint& bigint::operator>>=(unsigned int n) { *this = *this >> n; return *this; }

static unsigned int toUint(const bigint& b)
{
	unsigned int r = 0;
	for (size_t i = 0; i < b.str().size(); ++i)
		r = r * 10 + (b.str()[i] - '0');
	return r;
}

bigint  bigint::operator<<(const bigint& n) const { return *this << toUint(n); }
bigint  bigint::operator>>(const bigint& n) const { return *this >> toUint(n); }
bigint& bigint::operator<<=(const bigint& n) { return *this <<= toUint(n); }
bigint& bigint::operator>>=(const bigint& n) { return *this >>= toUint(n); }

/* ---------- 4) Karsilastirma: once uzunluk, sonra string ---------- */
bool bigint::operator==(const bigint& o) const { return _n == o._n; }
bool bigint::operator!=(const bigint& o) const { return !(*this == o); }
bool bigint::operator<(const bigint& o) const
{
	if (_n.size() != o._n.size())
		return _n.size() < o._n.size();
	return _n < o._n;
}
bool bigint::operator>(const bigint& o) const  { return o < *this; }
bool bigint::operator<=(const bigint& o) const { return !(o < *this); }
bool bigint::operator>=(const bigint& o) const { return !(*this < o); }

/* ---------- 5) Yazdirma ---------- */
std::ostream& operator<<(std::ostream& os, const bigint& b)
{
	os << b.str();
	return os;
}
