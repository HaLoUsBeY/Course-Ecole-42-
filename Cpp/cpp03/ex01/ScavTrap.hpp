#ifndef SCAVTRAP_HPP
#define SCAVTRAP_HPP

#include "ClapTrap.hpp"

class ScavTrap : public ClapTrap {
    public:
        // --- Orthodox Canonical Form ---
        ScavTrap();
        ScavTrap(const std::string& name);
        ScavTrap(const ScavTrap& src);
        ScavTrap& operator=(const ScavTrap& rhs);
        ~ScavTrap();

        // --- Overridden (Ezilmiş) ve Yeni Fonksiyonlar ---
        void attack(const std::string& target);
        void guardGate();
};

#endif