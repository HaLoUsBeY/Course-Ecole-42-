#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Array.hpp"

#define MAX_VAL 750

// const referans aldığı için operator[]'ın const sürümü çağrılır.
template <typename T>
static void printArray(const std::string & name, const Array<T> & arr)
{
    std::cout << name << " (size " << arr.size() << "): ";
    for (unsigned int i = 0; i < arr.size(); i++)
        std::cout << "[" << arr[i] << "] ";
    std::cout << std::endl;
}

static void defaultValueTest()
{
    // Subject'teki ipucu: new int() değeri 0 ile başlatır.
    int * a = new int();
    std::cout << "*a = " << *a << std::endl;
    delete a;

    Array<int> numbers(5);
    printArray("Array<int>(5)", numbers);
}

static void emptyTest()
{
    Array<int> empty;
    printArray("empty", empty);

    try
    {
        empty[0] = 42;
        std::cout << "ERROR: no exception" << std::endl;
    }
    catch (const std::exception & e)
    {
        std::cout << "empty[0]: " << e.what() << std::endl;
    }
}

static void copyTest()
{
    Array<int> original(5);
    for (unsigned int i = 0; i < original.size(); i++)
        original[i] = i * 10;

    Array<int> copy(original);
    copy[0] = 999;
    std::cout << "copy constructor, then copy[0] = 999" << std::endl;
    printArray("original", original);
    printArray("copy    ", copy);

    Array<int> assigned(2);
    assigned = original;
    original[4] = -1;
    std::cout << "assignment, then original[4] = -1" << std::endl;
    printArray("original", original);
    printArray("assigned", assigned);

    // Kendine atama: veri kaybolmamalı. (Referans, clang'in
    // -Wself-assign uyarısını önler.)
    Array<int> & same = assigned;
    assigned = same;
    printArray("self-assigned", assigned);
}

static void outOfBoundsTest()
{
    Array<int> numbers(3);
    const Array<int> constNumbers(3);

    try
    {
        numbers[3] = 1;
        std::cout << "ERROR: no exception" << std::endl;
    }
    catch (const std::exception & e)
    {
        std::cout << "numbers[3]: " << e.what() << std::endl;
    }

    try
    {
        numbers[-1] = 1;
        std::cout << "ERROR: no exception" << std::endl;
    }
    catch (const std::exception & e)
    {
        std::cout << "numbers[-1]: " << e.what() << std::endl;
    }

    try
    {
        std::cout << constNumbers[100] << std::endl;
        std::cout << "ERROR: no exception" << std::endl;
    }
    catch (const std::exception & e)
    {
        std::cout << "constNumbers[100]: " << e.what() << std::endl;
    }

    // Aşağıdaki satır derlenmez: const dizinin elemanı değiştirilemez.
    // constNumbers[0] = 5;
}

static void stringTest()
{
    Array<std::string> words(3);
    printArray("Array<std::string>(3)", words);

    words[0] = "hello";
    words[1] = "42";
    words[2] = "istanbul";

    Array<std::string> other;
    other = words;
    other[1] = "changed";
    printArray("words", words);
    printArray("other", other);
}

// Subject ile verilen testin aynısı.
static int subjectTest()
{
    Array<int> numbers(MAX_VAL);
    int * mirror = new int[MAX_VAL];

    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }
    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            delete[] mirror;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch (const std::exception & e)
    {
        std::cerr << e.what() << std::endl;
    }
    for (int i = 0; i < MAX_VAL; i++)
        numbers[i] = rand();
    delete[] mirror;
    std::cout << "subject test: OK" << std::endl;
    return 0;
}

int main(void)
{
    std::cout << "=== Default values ===" << std::endl;
    defaultValueTest();

    std::cout << std::endl << "=== Empty array ===" << std::endl;
    emptyTest();

    std::cout << std::endl << "=== Deep copy ===" << std::endl;
    copyTest();

    std::cout << std::endl << "=== Out of bounds ===" << std::endl;
    outOfBoundsTest();

    std::cout << std::endl << "=== std::string ===" << std::endl;
    stringTest();

    std::cout << std::endl << "=== Subject test ===" << std::endl;
    return subjectTest();
}
