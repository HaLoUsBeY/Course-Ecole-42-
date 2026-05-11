#include "ScavTrap.hpp"

int main(void)
{
    ClapTrap cp("Efe Akman");
    ScavTrap sv("HAlil derviş oğlu");

    std::cout << "Created ClapTrap and ScavTrap" << std::endl;
    sv.attack("Halil Umut Meler");
    cp.attack("Sergen Yalcin");
    cp.takeDamage(100);
    sv.takeDamage(10);
    cp.beRepaired(13);
    sv.beRepaired(5);
    sv.guardGate();
    return 0;
}
