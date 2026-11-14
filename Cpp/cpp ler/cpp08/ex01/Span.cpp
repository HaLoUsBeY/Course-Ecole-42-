#include "Span.hpp"
#include <algorithm>

Span::Span() : max_(0)
{
}

Span::Span(unsigned int n) : max_(n)
{
}

Span::Span(Span const &other) : max_(other.max_), numbers_(other.numbers_)
{
}

Span &Span::operator=(Span const &other)
{
    if (this != &other)
    {
        max_ = other.max_;
        numbers_ = other.numbers_;
    }
    return *this;
}

Span::~Span()
{
}

void Span::addNumber(int number)
{
    if (numbers_.size() >= max_)
        throw std::out_of_range("Span is full");
    numbers_.push_back(number);
}

// Sıralı dizide en kısa mesafe her zaman yan yana iki sayı arasındadır.
// int - int taşabilir (INT_MAX - INT_MIN), bu yüzden long ile hesaplıyoruz.
long Span::shortestSpan() const
{
    if (numbers_.size() < 2)
        throw std::logic_error("not enough numbers to find a span");

    std::vector<int> sorted(numbers_);
    std::sort(sorted.begin(), sorted.end());

    long shortest = static_cast<long>(sorted[1]) - sorted[0];
    for (std::size_t i = 2; i < sorted.size(); i++)
    {
        long diff = static_cast<long>(sorted[i]) - sorted[i - 1];
        if (diff < shortest)
            shortest = diff;
    }
    return shortest;
}

// En uzun mesafe = en büyük - en küçük (sıralamaya gerek yok)
long Span::longestSpan() const
{
    if (numbers_.size() < 2)
        throw std::logic_error("not enough numbers to find a span");

    int smallest = *std::min_element(numbers_.begin(), numbers_.end());
    int largest = *std::max_element(numbers_.begin(), numbers_.end());
    return static_cast<long>(largest) - smallest;
}

unsigned int Span::size() const
{
    return static_cast<unsigned int>(numbers_.size());
}
