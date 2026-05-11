#include "Brain.hpp"

Brain::Brain() {
    std::cout << "Brain Default Constructor called" << std::endl;
    // Beyni boş fikirlerle dolduralım
    for (int i = 0; i < 100; i++) {
        this->_ideas[i] = "Empty idea";
    }
}

Brain::Brain(const Brain &src) {
    std::cout << "Brain Copy Constructor called" << std::endl;
    *this = src;
}

Brain &Brain::operator=(const Brain &rhs) {
    std::cout << "Brain Assignment Operator called" << std::endl;
    if (this != &rhs) {
        // 100 fikri tek tek kopyalıyoruz (Deep Copy'nin temeli)
        for (int i = 0; i < 100; i++) {
            this->_ideas[i] = rhs._ideas[i];
        }
    }
    return *this;
}

Brain::~Brain() {
    std::cout << "Brain Destructor called" << std::endl;
}