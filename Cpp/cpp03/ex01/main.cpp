#include "ScavTrap.hpp"

int main(void) {
    std::cout << "========================================" << std::endl;
    std::cout << "         SCAVTRAP CREATION TEST         " << std::endl;
    std::cout << "========================================" << std::endl;
    
    ScavTrap uav("SpeedyBee"); // Önce ClapTrap sonra ScavTrap logu gelmeli!

    std::cout << "\n========================================" << std::endl;
    std::cout << "              ACTION TEST               " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // ScavTrap'in kendi özel mesajıyla saldırması lazım (20 hasar)
    uav.attack("Signal Interference"); 
    
    // ClapTrap'ten miras alınan yetenekler kusursuz çalışmalı
    uav.takeDamage(40);
    uav.beRepaired(15);
    
    // Yeni yetenek
    uav.guardGate();

    std::cout << "\n========================================" << std::endl;
    std::cout << "           COPY & DEEP TEST             " << std::endl;
    std::cout << "========================================" << std::endl;
    
    ScavTrap uav_copy(uav);
    uav_copy.attack("Emax Motor");
    uav_copy.takeDamage(100); // Kopyayı öldürüyoruz

    std::cout << "\n========================================" << std::endl;
    std::cout << "              DESTRUCTION               " << std::endl;
    std::cout << "========================================" << std::endl;
    
    // Önce ScavTrap sonra ClapTrap logu gelerek ölmeli!
    return 0;
}