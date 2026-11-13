#include "vect2.hpp"

vect2::vect2(){x = 0; y = 0;}
vect2::vect2(int a, int b){x = a; y = b;}
vect2& vect2::operator=(const vect2& b){x = b.x; y = b.y;}
vect2::~vect2(){}


int& vect2::operator[](int i)
{
    if (i== 0)
        return x;
    return y;
}

int vect2::operator[](int i) const
{
    if (i== 0)
        return x;
    return y;
}

vect2& vect2::operator++(){x++; y++; return *this;}
vect2& vect2::operator--(){x--; y--; return *this;}
vect2 vect2::operator++(int){vect2 tmp = *this; x++; y++; return tmp;}
vect2 vect2::operator--(int){vect2 tmp = *this; x--; y--; return tmp;}

vect2& vect2::operator+=(const vect2& b) {x += b.x; y += b.y; return *this;}
vect2& vect2::operator-=(const vect2& b) {x -= b.x; y -= b.y; return *this;}
vect2& vect2::operator+=(int k) {x *= k; y *= k; return *this;}

vect2 vect2::operator+(const vect2& b) const {return vect2(x + b.x, y + b.y);}
vect2 vect2::operator-(const vect2& b) const {return vect2(x - b.x, y - b.y);}
vect2 vect2::operator*(int k) const {return vect2(x * k, y * k);}
vect2 vect2::operator-() const {return vect2(-x, -y);}

bool vect2::operator==(const vect2& b) const {return (x == b.x && y == b.y);}
bool vect2::operator!=(const vect2& b) const {return !(*this == b);}

vect2 operator*(int k, const vect2& v) {return v * k;}

std::ostream& operator<<(std::ostream& os, const vect2& v)
{
    os << "{" << v[0] << ", " << v[1] << "}";
    return os;
}

