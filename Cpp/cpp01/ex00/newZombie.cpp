#include "Zombie.hpp"

Zombie* newZombie(std::string name)//zombie created
{
	Zombie *zombie;//new pointer
	zombie = new Zombie(name);//heap data and ->constructor
	return (zombie);//return pointer
}
