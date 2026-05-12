#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap c;
    ClapTrap a("Demba Ba");
    ClapTrap b(a);
    std::cout << std::endl << b.getter() << std::endl ;
    c.getters();
    return 0;
}