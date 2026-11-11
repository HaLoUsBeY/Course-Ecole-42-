#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
private:
	int v[2];                      // v[0] = x, v[1] = y

public:
	vect2();                       // {0, 0}
	vect2(int x, int y);
	vect2(const vect2& o);
	vect2& operator=(const vect2& o);
	~vect2();

	int&       operator[](int i);          // v1[1] = 12;
	const int& operator[](int i) const;    // const v3[1]

	vect2& operator++();           // ++v
	vect2  operator++(int);        // v++
	vect2& operator--();
	vect2  operator--(int);

	vect2& operator+=(const vect2& o);
	vect2& operator-=(const vect2& o);
	vect2& operator*=(int k);

	vect2 operator+(const vect2& o) const;
	vect2 operator-(const vect2& o) const;
	vect2 operator*(int k) const;          // v * 2
	vect2 operator-() const;               // -v

	bool operator==(const vect2& o) const;
	bool operator!=(const vect2& o) const;
};

vect2 operator*(int k, const vect2& a);   // 3 * v  (sinif disinda)
std::ostream& operator<<(std::ostream& os, const vect2& a);

#endif
