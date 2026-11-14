#ifndef SPAN_HPP
#define SPAN_HPP

#include <vector>
#include <iterator>
#include <stdexcept>

class Span
{
public:
    Span();
    Span(unsigned int n);
    Span(Span const &other);
    Span &operator=(Span const &other);
    ~Span();

    void addNumber(int number);

    // Bir iterator aralığındaki [first, last) tüm sayıları tek çağrıda ekler
    template <typename Iterator>
    void addRange(Iterator first, Iterator last);

    long shortestSpan() const;
    long longestSpan() const;
    unsigned int size() const;

private:
    unsigned int max_;
    std::vector<int> numbers_;
};

#include "Span.tpp"

#endif
