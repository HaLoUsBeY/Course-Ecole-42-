#ifndef BRAIN_HPP
#define BRAIN_HPP

#include <iostream>
#include <string>

class Brain
{
    private:
        std::string _ideas[100];//Encapsulation

    public:
        Brain();
        Brain(const Brain &src);
        Brain &operator=(const Brain &rhs);
        ~Brain();
};

#endif