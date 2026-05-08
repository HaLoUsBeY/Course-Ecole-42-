#include "Zombie.hpp"

int main(void)
{
    int N = 5;

    Zombie* myHorde = zombieHorde(N, "HordeWalker");
    
    if (!myHorde)
	{
        std::cerr << "Failed to create zombie horde (Invalid number or allocation failed)." << std::endl;
        return 1;
    }
    
    for (int i = 0; i < N; i++)
        myHorde[i].announce();
        
    delete[] myHorde;
    
    return 0;
}
