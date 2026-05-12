#include "ClapTrap.hpp"

// Default Constructor
ClapTrap::ClapTrap() : _name("Unnamed"), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    this->cagne = new std::string[3];
    this->cagne[0] = "abc";
    this->cagne[1] = "ghj";
    this->cagne[2] = "def";
    std::cout << "ClapTrap Default Constructor called for " << this->_name << std::endl;
}

// Parameter Constructor
ClapTrap::ClapTrap(const std::string& name) : _name(name), _hitPoints(10), _energyPoints(10), _attackDamage(0)
{
    this->cagne = new std::string[3];
    this->cagne[0] = "abc";
    this->cagne[1] = "ghj";
    this->cagne[2] = "def";
    std::cout << "ClapTrap Parameterized Constructor called for " << this->_name << std::endl;
}

// Copy Constructor
ClapTrap::ClapTrap(const ClapTrap& src)
{
    std::cout << "ClapTrap Copy Constructor called" << std::endl;
    *this = src;
}

// Assignment Operator
// ClapTrap& ClapTrap::operator=(const ClapTrap& rhs)
// {
//     std::cout << "ClapTrap Copy Assignment Operator called" << std::endl;
//     if (this != &rhs)
//     {
//         this->_name = rhs._name;
//         this->_hitPoints = rhs._hitPoints;
//         this->_energyPoints = rhs._energyPoints;
//         this->_attackDamage = rhs._attackDamage;
//         if (this->cagne)
//             delete[] this->cagne;
//         this->cagne = new std::string[3];
//         this->cagne[0] = rhs.cagne[0];
//         this->cagne[1] = rhs.cagne[1];
//         this->cagne[2] = rhs.cagne[2];

//     }
//     return *this;
// }

// Destructor
ClapTrap::~ClapTrap()
{
    delete[] this->cagne;
    std::cout << "ClapTrap Destructor called for " << this->_name << std::endl;
}

// --- Action Functions ---
void ClapTrap::attack(const std::string& target)
{
    if (this->_hitPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " is broken (0 HP) and cannot attack!" << std::endl;
        return;
    }
    if (this->_energyPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " is out of energy and cannot attack!" << std::endl;
        return;
    }
    this->_energyPoints--;
    std::cout << "ClapTrap " << this->_name << " attacks " << target 
              << ", causing " << this->_attackDamage << " points of damage!" << std::endl;
}

void ClapTrap::takeDamage(unsigned int amount)
{
    if (this->_hitPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " is already down! Stop hitting it!" << std::endl;
        return;
    }
    // Unsigned int check
    if (amount >= this->_hitPoints)
        this->_hitPoints = 0;
    else
        this->_hitPoints -= amount;
        
    std::cout << "ClapTrap " << this->_name << " takes " << amount 
              << " damage, dropping to " << this->_hitPoints << " HP!" << std::endl;
}

void ClapTrap::beRepaired(unsigned int amount)
{
    if (this->_hitPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " is totally destroyed and cannot be repaired!" << std::endl;
        return;
    }
    if (this->_energyPoints == 0)
    {
        std::cout << "ClapTrap " << this->_name << " has no energy to repair itself!" << std::endl;
        return;
    }
    
    this->_energyPoints--;
    this->_hitPoints += amount;
    std::cout << "ClapTrap " << this->_name << " repairs itself for " << amount 
              << " HP! Current HP: " << this->_hitPoints << std::endl;
}
std::string ClapTrap::getter(void) const
{
    return this->_name ;
}
void ClapTrap::getters(void) const
{
    for(int i = 0; i < 3 ; i++)
    {
        std::cout << this->cagne[i] << std::endl;
    }
}
