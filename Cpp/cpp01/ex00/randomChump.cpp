#include "Zombie.hpp"

void randomChump(std::string name)
{
    Zombie temporaryZombie(name);//stack
    temporaryZombie.announce(); //stack object (.)
}//delete stack
