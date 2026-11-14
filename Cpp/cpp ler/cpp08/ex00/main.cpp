#include <iostream>
#include <iterator>
#include <vector>
#include <list>
#include <deque>
#include "easyfind.hpp"

// Bulursa değeri ve indeksini, bulamazsa exception mesajını yazar
template <typename T>
void testFind(T &container, int value)
{
    try
    {
        typename T::iterator it = easyfind(container, value);
        std::cout << "easyfind(" << value << ") -> found " << *it
                  << " at index " << std::distance(container.begin(), it) << std::endl;
    }
    catch (std::exception const &e)
    {
        std::cout << "easyfind(" << value << ") -> exception: " << e.what() << std::endl;
    }
}

int main()
{
    std::cout << "=== std::vector ===" << std::endl;
    std::vector<int> vec;
    for (int i = 1; i <= 5; i++)
        vec.push_back(i * 10);
    testFind(vec, 10);
    testFind(vec, 30);
    testFind(vec, 50);
    testFind(vec, 42);

    std::cout << std::endl << "=== std::list (first occurrence) ===" << std::endl;
    std::list<int> lst;
    lst.push_back(-5);
    lst.push_back(0);
    lst.push_back(7);
    lst.push_back(0);
    testFind(lst, 0);
    testFind(lst, -5);
    testFind(lst, 8);

    std::cout << std::endl << "=== std::deque ===" << std::endl;
    std::deque<int> deq;
    deq.push_back(100);
    deq.push_front(200);
    deq.push_back(300);
    testFind(deq, 200);
    testFind(deq, 300);
    testFind(deq, 0);

    std::cout << std::endl << "=== modify through returned iterator ===" << std::endl;
    *easyfind(vec, 30) = 33;
    testFind(vec, 30);
    testFind(vec, 33);

    std::cout << std::endl << "=== const container ===" << std::endl;
    std::vector<int> const constVec(vec);
    try
    {
        std::vector<int>::const_iterator it = easyfind(constVec, 40);
        std::cout << "easyfind(40) -> found " << *it << std::endl;
        easyfind(constVec, 30);
        std::cout << "this line should not be printed" << std::endl;
    }
    catch (std::exception const &e)
    {
        std::cout << "easyfind(30) -> exception: " << e.what() << std::endl;
    }

    std::cout << std::endl << "=== empty container ===" << std::endl;
    std::vector<int> empty;
    testFind(empty, 0);

    return 0;
}
