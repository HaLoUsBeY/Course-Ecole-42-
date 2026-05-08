#include "Zombie.hpp"

Zombie::Zombie()
{
    std::cout << "A nameless zombie spawns in the horde..." << std::endl;
}

Zombie::~Zombie()
{
    std::cout << this->name << " is destroyed." << std::endl;
}

void Zombie::setName(std::string name) {
    this->name = name;
}

void Zombie::announce(void)
{
    std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}