#ifndef VECT2_HPP
#define VECT2_HPP

#include <iostream>

class vect2
{
    private:
        int x;
        int y;
    public:
        vect2::vect2();
        vect2::vect2(int a, int b);
        vect2& vect2::operator=(const vect2& b);
        vect2::~vect2();

        int& vect2::operator[](int i);
        int vect2::operator[](int i) const;

        vect2& vect2::operator++();
        vect2& vect2::operator--();
        vect2 vect2::operator++(int);
        vect2 vect2::operator--(int);

        vect2& vect2::operator+=(const vect2& b) ;
        vect2& vect2::operator-=(const vect2& b) ;
        vect2& vect2::operator+=(int k) ;

        vect2 vect2::operator+(const vect2& b) const ;
        vect2 vect2::operator-(const vect2& b) const ;
        vect2 vect2::operator*(int k) const ;
        vect2 vect2::operator-() const ;

        bool vect2::operator==(const vect2& b) const ;
        bool vect2::operator!=(const vect2& b) const ;


};

vect2 operator*(int k, const vect2& v) ;

std::ostream& operator<<(std::ostream& os, const vect2& v);

#endif