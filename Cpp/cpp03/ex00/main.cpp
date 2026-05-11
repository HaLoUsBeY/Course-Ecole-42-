#include "ClapTrap.hpp"

int main(void)
{
    ClapTrap a("Demba Ba");

    std::cout << "\n--- BASIC ACTIONS ---" << std::endl;
    a.attack("YakupTv");
    a.beRepaired(5);

    std::cout << "\n--- DEATH TEST ---" << std::endl;
    a.takeDamage(20); 
    a.attack("YakupTv"); 
    a.beRepaired(10);    

    std::cout << "\n--- END ---" << std::endl;
    return 0;
}