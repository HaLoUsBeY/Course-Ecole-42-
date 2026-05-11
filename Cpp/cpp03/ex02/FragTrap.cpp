#include "FragTrap.hpp"

// Default Constructor
FragTrap::FragTrap(void) : ClapTrap() {
    this->_name = "Unnamed_Frag";
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "FragTrap default constructor called for " << this->_name << std::endl;
}

// Parametreli Constructor
FragTrap::FragTrap(std::string name) : ClapTrap(name) {
    this->_hitPoints = 100;
    this->_energyPoints = 100;
    this->_attackDamage = 30;
    std::cout << "FragTrap parameterized constructor called for " << this->_name << std::endl;
}

// Copy Constructor (Manuel Yaklaşım)
FragTrap::FragTrap(const FragTrap &copy) : ClapTrap(copy) {
    std::cout << "FragTrap copy constructor called" << std::endl;
    *this = copy; 
}

// Assignment Operator (Manuel Yaklaşım)
FragTrap &FragTrap::operator=(const FragTrap &copy) {
    std::cout << "FragTrap copy assignment operator called" << std::endl;
    if (this != &copy) {
        this->_name = copy._name;
        this->_hitPoints = copy._hitPoints;
        this->_energyPoints = copy._energyPoints;
        this->_attackDamage = copy._attackDamage;
    }
    return *this;
}

// Destructor
FragTrap::~FragTrap(void) {
    std::cout << "FragTrap destructor called for " << this->_name << std::endl;
}

// Yeni Yetenek
void FragTrap::highFivesGuys(void) {
    if (this->_hitPoints == 0 || this->_energyPoints == 0) {
        std::cout << "FragTrap " << this->_name << " is in no condition to high five anyone!" << std::endl;
        return;
    }
    std::cout << "FragTrap " << this->_name << " enthusiastically requests a positive high five! ✋" << std::endl;
}