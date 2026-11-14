#include <iostream>
#include <cstddef>
#include "Serializer.hpp"

static void printData(const Data* data)
{
    std::cout << "  id: " << data->id
              << ", name: " << data->name
              << ", score: " << data->score << std::endl;
}

static void roundTrip(Data* original)
{
    uintptr_t raw = Serializer::serialize(original);
    Data* restored = Serializer::deserialize(raw);

    std::cout << "original pointer : " << original << std::endl;
    std::cout << "serialized value : " << raw
              << " (hex: 0x" << std::hex << raw << std::dec << ")" << std::endl;
    std::cout << "restored pointer : " << restored << std::endl;
    if (restored == original)
        std::cout << "restored == original : OK" << std::endl;
    else
        std::cout << "restored == original : FAIL" << std::endl;
}

int main()
{
    std::cout << "===== Test 1: stack object =====" << std::endl;
    Data data;
    data.id = 42;
    data.name = "Marvin";
    data.score = 4.2;
    roundTrip(&data);
    printData(Serializer::deserialize(Serializer::serialize(&data)));

    std::cout << std::endl << "===== Test 2: modify through restored pointer =====" << std::endl;
    Data* restored = Serializer::deserialize(Serializer::serialize(&data));
    restored->score = 100.0;
    std::cout << "restored->score = 100.0 -> data.score: " << data.score << std::endl;

    std::cout << std::endl << "===== Test 3: heap object =====" << std::endl;
    Data* heap = new Data;
    heap->id = 7;
    heap->name = "heap data";
    heap->score = 0.5;
    roundTrip(heap);
    printData(Serializer::deserialize(Serializer::serialize(heap)));
    delete heap;

    std::cout << std::endl << "===== Test 4: NULL pointer =====" << std::endl;
    std::cout << "serialize(NULL) : " << Serializer::serialize(NULL) << std::endl;
    if (Serializer::deserialize(0) == NULL)
        std::cout << "deserialize(0) == NULL : OK" << std::endl;
    else
        std::cout << "deserialize(0) == NULL : FAIL" << std::endl;
    return 0;
}
