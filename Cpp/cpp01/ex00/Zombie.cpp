#include "Zombie.hpp"

Zombie::Zombie(std::string name) : name(name)
{
    std::cout << "Zombie " << this->name << " has risen from the grave!" << std::endl;
}

Zombie::~Zombie()
{
    std::cout << this->name << " is finally dead for real..." << std::endl;
}

void Zombie::announce(void)
{
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}
