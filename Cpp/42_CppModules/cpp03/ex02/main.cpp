#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main()
{
	ClapTrap c_trap("Caitlyn");
	ScavTrap s_trap("Shaco");
	FragTrap f_trap("Fiora");

	c_trap.attack("Terrorist");
	s_trap.attack("Terrorist");
	f_trap.attack("Terrorist");
	f_trap.highFivesGuys();
	s_trap.guardGate();
	f_trap.takeDamage(80);
	f_trap.beRepaired(30);
	f_trap.takeDamage(60);
	f_trap.attack("Ghost");

	return 0;
}