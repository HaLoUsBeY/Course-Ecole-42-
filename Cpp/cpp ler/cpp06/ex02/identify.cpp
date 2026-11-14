#include "identify.hpp"
#include "A.hpp"
#include "B.hpp"
#include "C.hpp"

#include <iostream>
#include <cstdlib>
#include <exception>

// Rastgele A, B veya C üretir (srand main'de bir kez çağrılır)
Base* generate(void)
{
    int choice = std::rand() % 3;

    if (choice == 0)
        return new A;
    if (choice == 1)
        return new B;
    return new C;
}

// Pointer ile: dynamic_cast başarısızsa NULL döner
void identify(Base* p)
{
    if (dynamic_cast<A*>(p) != NULL)
        std::cout << "A" << std::endl;
    else if (dynamic_cast<B*>(p) != NULL)
        std::cout << "B" << std::endl;
    else if (dynamic_cast<C*>(p) != NULL)
        std::cout << "C" << std::endl;
    else
        std::cout << "Unknown" << std::endl;
}

/*
 * Referans ile: NULL referans olmadığı için dynamic_cast başarısızsa
 * std::bad_cast fırlatır. bad_cast'in başlığını eklemek subject'te yasak;
 * bad_cast std::exception'dan türediği için onu std::exception ile yakalıyoruz.
 */
void identify(Base& p)
{
    try
    {
        (void)dynamic_cast<A&>(p);
        std::cout << "A" << std::endl;
        return;
    }
    catch (const std::exception&)
    {
    }
    try
    {
        (void)dynamic_cast<B&>(p);
        std::cout << "B" << std::endl;
        return;
    }
    catch (const std::exception&)
    {
    }
    try
    {
        (void)dynamic_cast<C&>(p);
        std::cout << "C" << std::endl;
        return;
    }
    catch (const std::exception&)
    {
    }
    std::cout << "Unknown" << std::endl;
}
