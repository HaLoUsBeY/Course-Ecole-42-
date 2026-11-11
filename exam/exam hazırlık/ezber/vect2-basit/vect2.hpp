#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
private:
	int x;
	int y;

public:
	// 1) OCF
	vect2();
	vect2(int a, int b);
	vect2(const vect2& o);
	vect2& operator=(const vect2& o);
	~vect2();

	// 2) [] : v[0] = x, v[1] = y
	int& operator[](int i);
	int  operator[](int i) const;

	// 3) ++ --
	vect2& operator++();
	vect2  operator++(int);
	vect2& operator--();
	vect2  operator--(int);

	// 4) += -= *=  (vect2 & doner)
	vect2& operator+=(const vect2& o);
	vect2& operator-=(const vect2& o);
	vect2& operator*=(int k);

	// 5) + - *  (yeni vect2 doner, const)
	vect2 operator+(const vect2& o) const;
	vect2 operator-(const vect2& o) const;
	vect2 operator*(int k) const;
	vect2 operator-() const;

	// 6) == !=
	bool operator==(const vect2& o) const;
	bool operator!=(const vect2& o) const;
};

vect2 operator*(int k, const vect2& v);                // 3 * v
std::ostream& operator<<(std::ostream& os, const vect2& v);

#endif
