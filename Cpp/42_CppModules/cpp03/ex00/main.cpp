#include "ClapTrap.hpp"

int main()
{
	ClapTrap trap("Caitlyn");

	trap.attack("Terrorist");
	trap.takeDamage(5);
	trap.beRepaired(3);
	trap.takeDamage(20);
	trap.attack("Ghost");
	trap.beRepaired(10);

	return 0;
}