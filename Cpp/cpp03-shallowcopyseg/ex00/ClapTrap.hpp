#ifndef CLAPTRAP_HPP
#define CLAPTRAP_HPP

#include <iostream>
#include <string>

class ClapTrap
{
    private: //inheritance
        std::string     _name;
        unsigned int    _hitPoints;
        unsigned int    _energyPoints;
        unsigned int    _attackDamage;
        std::string*    cagne;

    public:
        // --- Orthodox Canonical Form ---
        ClapTrap();
        ClapTrap(const std::string& name);
        ClapTrap(const ClapTrap& src);
        // ClapTrap& operator=(const ClapTrap& rhs);
        ~ClapTrap();

        // --- Actions ---
        void attack(const std::string& target);
        void takeDamage(unsigned int amount);
        void beRepaired(unsigned int amount);
        std::string getter(void) const;
        void getters(void) const;

};

#endif