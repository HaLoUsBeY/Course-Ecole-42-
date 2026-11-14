#include <iostream>
#include <cstdlib>
#include <ctime>
#include "identify.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

static void identifyBoth(Base* p)
{
    std::cout << "  identify(Base*) : ";
    identify(p);
    std::cout << "  identify(Base&) : ";
    identify(*p);
}

int main()
{
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    std::cout << "===== Test 1: known types =====" << std::endl;
    A a;
    B b;
    C c;
    std::cout << "expected A" << std::endl;
    identifyBoth(&a);
    std::cout << "expected B" << std::endl;
    identifyBoth(&b);
    std::cout << "expected C" << std::endl;
    identifyBoth(&c);

    std::cout << std::endl << "===== Test 2: random generate() =====" << std::endl;
    for (int i = 1; i <= 6; i++)
    {
        Base* random = generate();
        std::cout << "object " << i << std::endl;
        identifyBoth(random);
        delete random;
    }

    std::cout << std::endl << "===== Test 3: plain Base (not A/B/C) =====" << std::endl;
    Base base;
    identifyBoth(&base);

    std::cout << std::endl << "===== Test 4: NULL pointer =====" << std::endl;
    Base* nothing = NULL;
    std::cout << "  identify(Base*) : ";
    identify(nothing);
    return 0;
}
