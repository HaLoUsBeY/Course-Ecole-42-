#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
    std::cout << "--- CREATING THE FAMILY ---" << std::endl;
    ClapTrap ct("Clappy");
    ScavTrap st("Scavy");
    FragTrap ft("Fraggy");

    std::cout << "\n--- ATTACK COMPARISON ---" << std::endl;
    ct.attack("Target"); // Orijinal ClapTrap mesajı
    st.attack("Target"); // Ezilmiş (Overridden) Vahşi ScavTrap mesajı
    ft.attack("Target"); // FragTrap kendi attack'ı olmadığı için Orijinal ClapTrap mesajını kullanır!

    std::cout << "\n--- SPECIAL ABILITIES ---" << std::endl;
    st.guardGate();
    ft.highFivesGuys();

    std::cout << "\n--- DAMAGE & REPAIR ---" << std::endl;
    ft.takeDamage(80);
    ft.beRepaired(30);

    std::cout << "\n--- DESTRUCTION ---" << std::endl;
    return 0;
}