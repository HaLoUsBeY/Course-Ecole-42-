#include "ClapTrap.hpp"
#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main(void)
{
    ClapTrap ct("Laz Ziya");
    ScavTrap st("Hüsrev Ağa");
    FragTrap ft("Memati");

    ct.attack("Büyük İskender");
    st.attack("Çeto");
    ft.attack("Testere Necmi");

    st.guardGate();
    ft.highFivesGuys();

    st.takeDamage(80);
    st.beRepaired(20);
    ft.takeDamage(50);
    ft.beRepaired(30);

    return 0;
}