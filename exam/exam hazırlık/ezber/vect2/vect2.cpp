#include "vect2.hpp"

/* 1) OCF */
vect2::vect2() { v[0] = 0; v[1] = 0; }
vect2::vect2(int x, int y) { v[0] = x; v[1] = y; }
vect2::vect2(const vect2& o) { v[0] = o.v[0]; v[1] = o.v[1]; }
vect2& vect2::operator=(const vect2& o) { v[0] = o.v[0]; v[1] = o.v[1]; return *this; }
vect2::~vect2() {}

/* 2) [] : biri yazilabilir, biri const nesne icin */
int&       vect2::operator[](int i)       { return v[i]; }
const int& vect2::operator[](int i) const { return v[i]; }

/* 3) ++ / -- : on ek *this doner, son ek eskiyi doner */
vect2& vect2::operator++() { v[0]++; v[1]++; return *this; }
vect2  vect2::operator++(int) { vect2 eski = *this; ++(*this); return eski; }
vect2& vect2::operator--() { v[0]--; v[1]--; return *this; }
vect2  vect2::operator--(int) { vect2 eski = *this; --(*this); return eski; }

/* 4) += -= *= asil isi yapar */
vect2& vect2::operator+=(const vect2& o) { v[0] += o.v[0]; v[1] += o.v[1]; return *this; }
vect2& vect2::operator-=(const vect2& o) { v[0] -= o.v[0]; v[1] -= o.v[1]; return *this; }
vect2& vect2::operator*=(int k) { v[0] *= k; v[1] *= k; return *this; }

/* 5) + - * : kopya al, += ile hallet */
vect2 vect2::operator+(const vect2& o) const { vect2 s = *this; s += o; return s; }
vect2 vect2::operator-(const vect2& o) const { vect2 s = *this; s -= o; return s; }
vect2 vect2::operator*(int k) const { vect2 s = *this; s *= k; return s; }
vect2 vect2::operator-() const { return vect2(-v[0], -v[1]); }
vect2 operator*(int k, const vect2& a) { return a * k; }

/* 6) karsilastirma */
bool vect2::operator==(const vect2& o) const { return v[0] == o.v[0] && v[1] == o.v[1]; }
bool vect2::operator!=(const vect2& o) const { return !(*this == o); }

/* 7) yazdirma: {x, y} */
std::ostream& operator<<(std::ostream& os, const vect2& a)
{
	os << "{" << a[0] << ", " << a[1] << "}";
	return os;
}
