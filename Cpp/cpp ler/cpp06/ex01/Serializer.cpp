#include "Serializer.hpp"

/* ===================== OCF (private) ===================== */

Serializer::Serializer()
{
}

Serializer::Serializer(const Serializer& other)
{
    (void)other;
}

Serializer& Serializer::operator=(const Serializer& other)
{
    (void)other;
    return *this;
}

Serializer::~Serializer()
{
}

/* ===================== Static metotlar ===================== */

// Pointer -> tam sayı: bitler aynen korunur, sadece tip yeniden yorumlanır
uintptr_t Serializer::serialize(Data* ptr)
{
    return reinterpret_cast<uintptr_t>(ptr);
}

// Tam sayı -> pointer: serialize'ın tersi
Data* Serializer::deserialize(uintptr_t raw)
{
    return reinterpret_cast<Data*>(raw);
}
