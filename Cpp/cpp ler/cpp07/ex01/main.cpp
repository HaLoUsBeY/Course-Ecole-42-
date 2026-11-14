#include <iostream>
#include <string>
#include "iter.hpp"

// --- iter'e verilecek fonksiyonlar ---

template <typename T>
void print(const T & x)
{
    std::cout << "[" << x << "] ";
}

template <typename T>
void increment(T & x)
{
    x++;
}

void addExclamation(std::string & s)
{
    s += "!";
}

// Parametreyi değerle alan normal fonksiyon da çalışır.
void printSquare(int n)
{
    std::cout << n * n << " ";
}

// --- testler ---

static void intTest()
{
    int numbers[5] = {1, 2, 3, 4, 5};

    std::cout << "before:    ";
    iter(numbers, 5, print<int>);
    std::cout << std::endl;

    iter(numbers, 5, increment<int>);

    std::cout << "increment: ";
    iter(numbers, 5, print<int>);
    std::cout << std::endl;

    std::cout << "squares:   ";
    iter(numbers, 5, printSquare);
    std::cout << std::endl;
}

static void stringTest()
{
    std::string words[3] = {"hello", "42", "istanbul"};

    std::cout << "before: ";
    iter(words, 3, print<std::string>);
    std::cout << std::endl;

    iter(words, 3, addExclamation);

    std::cout << "after:  ";
    iter(words, 3, print<std::string>);
    std::cout << std::endl;
}

static void constTest()
{
    const int constNumbers[4] = {10, 20, 30, 40};
    const std::string constWords[2] = {"const", "string"};

    std::cout << "const int:    ";
    iter(constNumbers, 4, print<int>);
    std::cout << std::endl;

    std::cout << "const string: ";
    iter(constWords, 2, print<std::string>);
    std::cout << std::endl;

    // Aşağıdaki satır derlenmez: const eleman değiştirilemez.
    // iter(constNumbers, 4, increment<int>);
}

static void otherTest()
{
    char letters[4] = {'a', 'b', 'c', 'd'};
    double values[3] = {1.5, 2.5, 3.5};

    iter(letters, 4, increment<char>);
    std::cout << "chars + 1:  ";
    iter(letters, 4, print<char>);
    std::cout << std::endl;

    iter(values, 3, increment<double>);
    std::cout << "double + 1: ";
    iter(values, 3, print<double>);
    std::cout << std::endl;

    // Uzunluk 0: fonksiyon hiç çağrılmaz.
    std::cout << "length 0:   ";
    iter(values, 0, print<double>);
    std::cout << "(nothing)" << std::endl;
}

int main(void)
{
    std::cout << "=== int array ===" << std::endl;
    intTest();

    std::cout << std::endl << "=== std::string array ===" << std::endl;
    stringTest();

    std::cout << std::endl << "=== const arrays ===" << std::endl;
    constTest();

    std::cout << std::endl << "=== other types ===" << std::endl;
    otherTest();
    return 0;
}
