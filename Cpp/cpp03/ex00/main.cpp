#include "ClapTrap.hpp"

int main(void) {
    std::cout << "\n--- CREATION ---" << std::endl;
    ClapTrap a("Halo");
    ClapTrap b("Enemy");

    std::cout << "\n--- ACTION TEST ---" << std::endl;
    a.attack("Enemy");
    b.takeDamage(0); // Halo'nun atağı 0 olduğu için Enemy 0 hasar alır.

    a.beRepaired(5); // 5 can yeniler
    a.takeDamage(9); // 9 hasar alır (canı 6'ya düşer)

    std::cout << "\n--- EXHAUSTION (ENERJI BITIRME) TEST ---" << std::endl;
    // Halo 10 kere saldırıp enerjisini sıfırlasın
    for (int i = 0; i < 9; i++) {
        a.attack("the air");
    }

    std::cout << "\n--- DEATH (OLUM) TEST ---" << std::endl;
    b.takeDamage(20); // Enemy tek yer ve canı 0 olur
    b.attack("Halo"); // Canı 0 olduğu için saldıramamalı!
    b.beRepaired(10); // Canı 0 olduğu için tamir de olamamalı!

    std::cout << "\n--- DESTRUCTION ---" << std::endl;
    return 0;
}