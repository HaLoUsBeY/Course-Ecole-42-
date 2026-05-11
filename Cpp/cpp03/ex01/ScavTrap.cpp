#include "ScavTrap.hpp"

// Default Constructor
ScavTrap::ScavTrap(void) : ClapTrap() {
    this->_name = "Unnamed_Scav"; // Alt tire eklendi!
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap default constructor called for " << this->_name << std::endl;
}

// Parametreli Constructor
ScavTrap::ScavTrap(std::string name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 50;
    this->_attackDamage = 20;
    std::cout << "ScavTrap parameterized constructor called for " << this->_name << std::endl;
}

// Copy Constructor (Manuel Yaklaşım - Evaluator Tuzağı)
ScavTrap::ScavTrap(const ScavTrap &copy) : ClapTrap(copy) {
    std::cout << "ScavTrap copy constructor called" << std::endl;
    *this = copy; 
}

// Assignment Operator (Manuel Yaklaşım)
ScavTrap &ScavTrap::operator=(const ScavTrap &copy) {
    std::cout << "ScavTrap copy assignment operator called" << std::endl;
    if (this != &copy) {
        this->_name = copy._name;
        this->_hitPoints = copy._hitPoints;
        this->_energyPoints = copy._energyPoints;
        this->_attackDamage = copy._attackDamage;
    }
    return *this;
}

// Destructor
ScavTrap::~ScavTrap(void) {
    std::cout << "ScavTrap destructor called for " << this->_name << std::endl;
}

// Overridden (Ezilmiş) Attack Fonksiyonu
void ScavTrap::attack(const std::string &target) {
    if (this->_hitPoints == 0 || this->_energyPoints == 0) {
        std::cout << "ScavTrap " << this->_name << " can't attack, no hit points or energy points left!" << std::endl;
        return;
    }
    this->_energyPoints--; 
    std::cout << "ScavTrap " << this->_name << " violently strikes " << target 
              << ", causing " << this->_attackDamage << " points of massive damage!" << std::endl;
}

// Yeni Yetenek
void ScavTrap::guardGate(void) {
    std::cout << "ScavTrap " << this->_name << " is now in gate keeper mode. None shall pass!" << std::endl;
}