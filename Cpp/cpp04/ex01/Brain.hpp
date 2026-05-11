#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>

class Brain
{
    private:
        // Fikirler kesinlikle private olmalı! (Encapsulation)
        std::string _ideas[100];

    public:
        Brain();
        Brain(const Brain &src);
        Brain &operator=(const Brain &rhs);
        ~Brain();
};

#endif