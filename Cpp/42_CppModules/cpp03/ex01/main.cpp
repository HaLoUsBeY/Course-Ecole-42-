#include "ClapTrap.hpp"
#include "ScavTrap.hpp"

int main()
{
	ClapTrap c_trap("Caitlyn");
	ScavTrap s_trap("Shaco");

	c_trap.attack("Terrorist");
	s_trap.attack("Terrorist");
	s_trap.guardGate();
	s_trap.takeDamage(80);
	s_trap.beRepaired(20);
	s_trap.takeDamage(50);
	s_trap.attack("Ghost");

	return 0;
}