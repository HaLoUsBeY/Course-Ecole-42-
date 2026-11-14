#ifndef WHATEVER_HPP
#define WHATEVER_HPP

// Şablonlar header'da tanımlanır: derleyici her tip için kodu burada üretir.

template <typename T>
void swap(T & a, T & b)
{
    T tmp = a;

    a = b;
    b = tmp;
}

// Eşitlerse ikinci parametre (b) döner.
template <typename T>
const T & min(const T & a, const T & b)
{
    if (a < b)
        return a;
    return b;
}

// Eşitlerse ikinci parametre (b) döner.
template <typename T>
const T & max(const T & a, const T & b)
{
    if (a > b)
        return a;
    return b;
}

#endif
