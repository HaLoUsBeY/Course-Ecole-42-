#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <cstdlib>   // NULL (subject'in test main'i rand/srand'ı da buradan alır)
#include <exception>

template <typename T>
class Array
{
public:
    Array();
    Array(unsigned int n);
    Array(const Array & other);
    Array & operator=(const Array & other);
    ~Array();

    T & operator[](unsigned int index);
    const T & operator[](unsigned int index) const;
    unsigned int size() const;

    class OutOfBoundsException : public std::exception
    {
    public:
        virtual const char * what() const throw();
    };

private:
    T * data_;
    unsigned int size_;
};

// Şablonun gövdesi .tpp'de; derleyici onu görebilsin diye header'a eklenir.
#include "Array.tpp"

#endif
