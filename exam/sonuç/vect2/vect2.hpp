#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
    private:
        int x;
        int y;
    public:
        vect2();
        vect2(int a, int b);
        vect2(const vect2& o);
        vect2& operator=(const vect2& o);
        ~vect2();

        int& operator[](int i);
        int operator[](int i) const;

        vect2& operator++();
        vect2& operator--();      
        vect2 operator++(int);      
        vect2 operator--(int);

        vect2& operator+=(const vect2& o);
        vect2& operator-=(const vect2& o);
        vect2& operator*=(int k);

        vect2 operator+(const vect2& o) const;
        vect2 operator-(const vect2& o) const;
        vect2 operator*(int k) const;
        vect2 operator-() const;

        bool operator==(const vect2& o) const;
        bool operator!=(const vect2& o) const;

};

vect2 operator*(int k, const vect2& v);

std::ostream& operator<<(std::ostream& os, const vect2& v);

#endif