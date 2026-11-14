#ifndef ITER_HPP
#define ITER_HPP

#include <cstddef>

// F: fonksiyon pointer'ı ya da şablon örneği (print<int> gibi) olabilir.

// Değiştirilebilir dizi: func elemanı T& ile alıp değiştirebilir.
template <typename T, typename F>
void iter(T * array, const size_t length, F func)
{
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}

// const dizi: elemanlar yalnızca const T& olarak verilir (sadece okuma).
template <typename T, typename F>
void iter(const T * array, const size_t length, F func)
{
    for (size_t i = 0; i < length; i++)
        func(array[i]);
}

#endif
