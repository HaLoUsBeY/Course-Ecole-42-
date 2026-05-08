#include "Zombie.hpp"

int main(void)
{
    Zombie* heapZombie1 = newZombie("Walker");
    Zombie* heapZombie2 = newZombie("Runner");
    
    heapZombie1->announce();//heap object(->)
    heapZombie2->announce();
    
    delete heapZombie1;
    delete heapZombie2;

    randomChump("Crawler");
    randomChump("Jumper");

    std::cout << "\nGood Bye" << std::endl;
    return 0;
}