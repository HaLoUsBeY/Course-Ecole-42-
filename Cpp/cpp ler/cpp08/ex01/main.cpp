#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <climits>
#include "Span.hpp"

static void printSpans(Span const &sp)
{
    try
    {
        long shortest = sp.shortestSpan();
        long longest = sp.longestSpan();
        std::cout << "shortest: " << shortest << ", longest: " << longest << std::endl;
    }
    catch (std::exception const &e)
    {
        std::cout << "exception: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "=== subject example ===" << std::endl;
    {
        Span sp = Span(5);

        sp.addNumber(6);
        sp.addNumber(3);
        sp.addNumber(17);
        sp.addNumber(9);
        sp.addNumber(11);

        std::cout << sp.shortestSpan() << std::endl;
        std::cout << sp.longestSpan() << std::endl;
    }

    std::cout << std::endl << "=== not enough numbers ===" << std::endl;
    {
        Span sp(3);
        printSpans(sp);
        sp.addNumber(42);
        printSpans(sp);
    }

    std::cout << std::endl << "=== Span is full ===" << std::endl;
    {
        Span sp(2);
        try
        {
            sp.addNumber(1);
            sp.addNumber(2);
            std::cout << "added 2 numbers" << std::endl;
            sp.addNumber(3);
            std::cout << "this line should not be printed" << std::endl;
        }
        catch (std::exception const &e)
        {
            std::cout << "exception: " << e.what() << std::endl;
        }

        Span zero(0);
        try
        {
            zero.addNumber(1);
            std::cout << "this line should not be printed" << std::endl;
        }
        catch (std::exception const &e)
        {
            std::cout << "Span(0): exception: " << e.what() << std::endl;
        }
    }

    std::cout << std::endl << "=== addRange (list + array) ===" << std::endl;
    {
        std::list<int> lst;
        lst.push_back(-10);
        lst.push_back(4);
        lst.push_back(25);
        int arr[] = {1, 100, 50};

        Span sp(6);
        sp.addRange(lst.begin(), lst.end());
        sp.addRange(arr, arr + 3);
        std::cout << "size: " << sp.size() << std::endl;
        printSpans(sp);
        try
        {
            sp.addRange(arr, arr + 1);
            std::cout << "this line should not be printed" << std::endl;
        }
        catch (std::exception const &e)
        {
            std::cout << "exception: " << e.what() << std::endl;
        }

        Span small(2);
        try
        {
            small.addRange(arr, arr + 3);
            std::cout << "this line should not be printed" << std::endl;
        }
        catch (std::exception const &e)
        {
            std::cout << "exception: " << e.what() << std::endl;
        }
        std::cout << "size after failed addRange: " << small.size() << std::endl;
    }

    std::cout << std::endl << "=== duplicates and extreme values ===" << std::endl;
    {
        Span dup(3);
        dup.addNumber(7);
        dup.addNumber(-3);
        dup.addNumber(7);
        printSpans(dup);

        Span sp(3);
        sp.addNumber(INT_MIN);
        sp.addNumber(INT_MAX);
        sp.addNumber(0);
        printSpans(sp);
    }

    std::cout << std::endl << "=== copy constructor / assignment ===" << std::endl;
    {
        Span a(4);
        a.addNumber(1);
        a.addNumber(10);

        Span b(a);
        b.addNumber(12);

        Span c(1);
        c = b;
        c.addNumber(100);

        std::cout << "a size: " << a.size() << std::endl;
        printSpans(a);
        std::cout << "b size: " << b.size() << std::endl;
        printSpans(b);
        std::cout << "c size: " << c.size() << std::endl;
        printSpans(c);
    }

    std::cout << std::endl << "=== 10 000 numbers (expected 3 and 29997) ===" << std::endl;
    {
        std::vector<int> v;
        for (int i = 0; i < 10000; i++)
            v.push_back(i * 3);
        std::reverse(v.begin(), v.end());

        Span sp(10000);
        sp.addRange(v.begin(), v.end());
        std::cout << "size: " << sp.size() << std::endl;
        printSpans(sp);
    }

    std::cout << std::endl << "=== 100 000 random numbers ===" << std::endl;
    {
        std::srand(static_cast<unsigned int>(std::time(NULL)));
        std::vector<int> v(100000);
        std::generate(v.begin(), v.end(), std::rand);

        Span sp(100000);
        sp.addRange(v.begin(), v.end());
        std::cout << "size: " << sp.size() << std::endl;
        printSpans(sp);
        std::cout << "check longest: "
                  << static_cast<long>(*std::max_element(v.begin(), v.end()))
                     - *std::min_element(v.begin(), v.end()) << std::endl;
    }

    return 0;
}
