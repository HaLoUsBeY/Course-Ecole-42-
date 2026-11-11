#include "vect2.hpp"

// 1) OCF
vect2::vect2() { x = 0; y = 0; }
vect2::vect2(int a, int b) { x = a; y = b; }
vect2::vect2(const vect2& o) { x = o.x; y = o.y; }
vect2& vect2::operator=(const vect2& o) { x = o.x; y = o.y; return *this; }
vect2::~vect2() {}

// 2) [] : 0 ise x, degilse y
int& vect2::operator[](int i)
{
	if (i == 0)
		return x;
	return y;
}
int vect2::operator[](int i) const
{
	if (i == 0)
		return x;
	return y;
}

// 3) ++ -- : on ek degistir ve kendini dondur, son ek eskiyi dondur
vect2& vect2::operator++() { x++; y++; return *this; }
vect2& vect2::operator--() { x--; y--; return *this; }
vect2 vect2::operator++(int) { vect2 eski = *this; x++; y++; return eski; }
vect2 vect2::operator--(int) { vect2 eski = *this; x--; y--; return eski; }

// 4) += -= *= : kendini degistir, *this dondur
vect2& vect2::operator+=(const vect2& o) { x += o.x; y += o.y; return *this; }
vect2& vect2::operator-=(const vect2& o) { x -= o.x; y -= o.y; return *this; }
vect2& vect2::operator*=(int k) { x *= k; y *= k; return *this; }

// 5) + - * : yeni vect2 olustur
vect2 vect2::operator+(const vect2& o) const { return vect2(x + o.x, y + o.y); }
vect2 vect2::operator-(const vect2& o) const { return vect2(x - o.x, y - o.y); }
vect2 vect2::operator*(int k) const { return vect2(x * k, y * k); }
vect2 vect2::operator-() const { return vect2(-x, -y); }

// 6) == !=
bool vect2::operator==(const vect2& o) const { return x == o.x && y == o.y; }
bool vect2::operator!=(const vect2& o) const { return !(*this == o); }

// 7) sinif disi: 3 * v  ve  yazdirma {x, y}
vect2 operator*(int k, const vect2& v) { return v * k; }

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
	os << "{" << v[0] << ", " << v[1] << "}";
	return os;
}
