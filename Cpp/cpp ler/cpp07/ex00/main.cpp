#include <iostream>
#include <string>
#include "whatever.hpp"

static void subjectTest()
{
    int a = 2;
    int b = 3;

    ::swap( a, b );
    std::cout << "a = " << a << ", b = " << b << std::endl;
    std::cout << "min( a, b ) = " << ::min( a, b ) << std::endl;
    std::cout << "max( a, b ) = " << ::max( a, b ) << std::endl;

    std::string c = "chaine1";
    std::string d = "chaine2";

    ::swap(c, d);
    std::cout << "c = " << c << ", d = " << d << std::endl;
    std::cout << "min( c, d ) = " << ::min( c, d ) << std::endl;
    std::cout << "max( c, d ) = " << ::max( c, d ) << std::endl;
}

static void equalTest()
{
    int x = 42;
    int y = 42;

    // Değerler aynı; adresleri karşılaştırarak hangisinin döndüğünü görürüz.
    std::cout << "x = " << x << ", y = " << y << std::endl;
    std::cout << "min(x, y) returns y: "
              << (&::min(x, y) == &y ? "yes" : "no") << std::endl;
    std::cout << "max(x, y) returns y: "
              << (&::max(x, y) == &y ? "yes" : "no") << std::endl;
}

static void otherTypesTest()
{
    char c1 = 'a';
    char c2 = 'z';
    ::swap(c1, c2);
    std::cout << "c1 = " << c1 << ", c2 = " << c2 << std::endl;
    std::cout << "min(c1, c2) = " << ::min(c1, c2) << std::endl;
    std::cout << "max(c1, c2) = " << ::max(c1, c2) << std::endl;

    double d1 = 3.14;
    double d2 = -2.5;
    ::swap(d1, d2);
    std::cout << "d1 = " << d1 << ", d2 = " << d2 << std::endl;
    std::cout << "min(d1, d2) = " << ::min(d1, d2) << std::endl;
    std::cout << "max(d1, d2) = " << ::max(d1, d2) << std::endl;

    // Şablon argümanı açıkça da verilebilir.
    std::cout << "max<float>(1.5f, 2.5f) = " << ::max<float>(1.5f, 2.5f) << std::endl;
}

int main(void)
{
    std::cout << "=== Subject test ===" << std::endl;
    subjectTest();

    std::cout << std::endl << "=== Equal values ===" << std::endl;
    equalTest();

    std::cout << std::endl << "=== Other types ===" << std::endl;
    otherTypesTest();
    return 0;
}
