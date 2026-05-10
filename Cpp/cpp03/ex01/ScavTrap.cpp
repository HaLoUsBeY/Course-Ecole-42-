#include "ScavTrap.hpp"

// Default Constructor
// Önce atası olan ClapTrap doğar, sonra ScavTrap'in kendi değerleri atanır.
ScavTrap::ScavTrap() : ClapTrap("Unnamed_Scav") {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap Default Constructor called for " << this->_name << std::endl;
}

// Parametreli Constructor
ScavTrap::ScavTrap(const std::string& name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap Parameterized Constructor called for " << this->_name << std::endl;
}

// Copy Constructor (Profesyonel yaklaşım)
// "src" nesnesini doğrudan ClapTrap'in kopya yapıcısına yolluyoruz. 
// O kendi içindeki isim, can, hasar ne varsa otomatik hallediyor!
ScavTrap::ScavTrap(const ScavTrap& src) : ClapTrap(src) {
    std::cout << "ScavTrap Copy Constructor called" << std::endl;
}

// Assignment Operator (Kalıtım mantığına uygun atama)
ScavTrap& ScavTrap::operator=(const ScavTrap& rhs) {
    std::cout << "ScavTrap Copy Assignment Operator called" << std::endl;
    if (this != &rhs) {
        // Tek tek this->_name = rhs._name demek yerine; üst sınıfın operatörünü çağırıyoruz:
        ClapTrap::operator=(rhs); 
    }
    return *this;
}

// Destructor
ScavTrap::~ScavTrap() {
    std::cout << "ScavTrap Destructor called for " << this->_name << std::endl;
}

// Overridden (Ezilmiş) Attack Fonksiyonu
// ClapTrap'in attack'ından farklı bir mesaj basmak zorunda (Subject Kuralı)
void ScavTrap::attack(const std::string& target) {
    if (this->_hitPoints == 0) {
        std::cout << "ScavTrap " << this->_name << " is just a pile of scrap and cannot attack!" << std::endl;
        return;
    }
    if (this->_energyPoints == 0) {
        std::cout << "ScavTrap " << this->_name << " is out of juice (0 EP) and cannot attack!" << std::endl;
        return;
    }

    this->_energyPoints--;
    std::cout << "ScavTrap " << this->_name << " violently strikes " << target 
              << " for " << this->_attackDamage << " points of massive damage!" << std::endl;
}

// Yeni Yetenek
void ScavTrap::guardGate() {
    std::cout << "ScavTrap " << this->_name << " has firmly entered Gate keeper mode. None shall pass!" << std::endl;
}