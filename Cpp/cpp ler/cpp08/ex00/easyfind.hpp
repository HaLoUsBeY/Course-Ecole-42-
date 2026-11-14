#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

// T: int tutan bir container (vector, list, deque ...).
// Bulursa ilk eşleşmenin iterator'unu döner,
// bulamazsa std::runtime_error fırlatır.
template <typename T>
typename T::iterator easyfind(T &container, int value);

// const container için aynı fonksiyon (const_iterator döner)
template <typename T>
typename T::const_iterator easyfind(T const &container, int value);

#include "easyfind.tpp"

#endif
