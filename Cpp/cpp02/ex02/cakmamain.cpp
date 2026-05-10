#include "Fixed.hpp"
#include <iostream>

// Ciktiyi guzel gostermek icin kucuk bir yardimci makro/fonksiyon mantigi
void printStatus(std::string islem, const Fixed& f) {
    std::cout << "- " << islem << "\n";
    std::cout << "  Insan Gozunden : " << f 
              << "\t| Makine Gozunden (RawBits) : " << f.getRawBits() << "\n\n";
}

int main(void) {
    std::cout << "========================================================\n";
    std::cout << "       EX02 EVALUATION TEST (BEYIND THE SCENES)         \n";
    std::cout << "========================================================\n\n";

    Fixed a(10);
    Fixed b(2.5f);
    Fixed c;

    std::cout << "--- 1. BASLANGIC DEGERLERI ---\n";
    printStatus("Fixed a(10)", a);
    printStatus("Fixed b(2.5f)", b);
    printStatus("Fixed c (Default)", c);

    std::cout << "--- 2. ARITMETIK VE ATAMA (c = a + b) ---\n";
    // Burada a ve b float'a cevrilip toplanir, sonra yeni Fixed uretilir.
    c = a + b; //a.operator+(b)
    printStatus("c = a + b  (Yani 10 + 2.5)", c);

    std::cout << "--- 3. ZINCIRLEME ATAMA (a = b = c) ---\n";
    // ISTE "UZAYA GITMEYEN" DEGERLERIN KANITI!
    // Eger operator= void donseydi bu satir compile error verirdi.
    // c once b'ye esitlenir, b'nin referansi doner, o referans da a'ya esitlenir.
    a = b = c;
    std::cout << "Sonuc: Hepsi ayni degere (12.5) sahip olmali.\n";
    printStatus("a'nin son hali", a);
    printStatus("b'nin son hali", b);


    std::cout << "--- 4. EPSILON MANTIGI (++a) ---\n";
    // Epsilon (0.00390625) nedir? RawBits'in sadece 1 artmasidir!
    Fixed e(0); // Icerisi tamamen sifir.
    printStatus("Baslangic e(0)", e);
    ++e;
    // Burada rawBits sifirdan 1'e cikacak. Insan bunu 1/256 (0.00390625) olarak gorecek.
    printStatus("++e yapildiktan sonra", e);


    std::cout << "--- 5. ZINCIRLEME ARTIRMA (++++x) ---\n";
    // ISTE REFERANS (Fixed&) DONMENIN BIR BASKA GUCU!
    // Eger ++ operatoru degeri kopya olarak (Fixed) donseydi, ikinci ++ bosa giderdi.
    // Fixed& dondugu icin ayni nesne uzerinde 2 kere ard arda islem yapilabilir.
    Fixed x(0);
    ++++x; 
    // rawBits 2 kere artacak (2 olacak). Insan bunu 2/256 (0.0078125) gorecek.
    printStatus("++++x (Ard arda 2 kere artirma)", x);


    std::cout << "--- 6. POSTFIX vs PREFIX FARKI (a++ vs ++a) ---\n";
    Fixed y(5);
    std::cout << "- y'nin ilk hali\n";
    std::cout << "  Insan: " << y << "\t| Makine: " << y.getRawBits() << "\n\n";
    
    // a++ bize sayinin ESKI HALINI (5) dondurur, ama arkadan rawbits artmistir.
    std::cout << "- cout << y++ (Ekrana eski hali basar, sonra artirir)\n";
    std::cout << "  Ekrana Basilan : " << y++ << "\n\n";

    // Simdi gercek guncel halini gorelim
    printStatus("y++ isleminden sonra y'nin guncel hali", y);


    std::cout << "--- 7. MIN / MAX TESTI ---\n";
    Fixed num1(42.42f);
    Fixed num2(42.43f);
    std::cout << "- num1: " << num1 << " | num2: " << num2 << "\n";
    std::cout << "- Fixed::max(num1, num2) Sonucu: " << Fixed::max(num1, num2) << "\n";

    std::cout << "\n========================================================\n";
    std::cout << "                 TEST TAMAMLANDI                        \n";
    std::cout << "========================================================\n";

    return 0;
}