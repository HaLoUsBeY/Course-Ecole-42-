#include "Cat.hpp"

Cat::Cat() : Animal() {
    this->_type = "Cat";
    this->_brain = new Brain(); // Doğarken beyni RAM'de yaratılır
    std::cout << "Cat Default Constructor called" << std::endl;
}

// DEEP COPY (Derin Kopya) TUZAĞI BURADA ÇÖZÜLÜYOR
Cat::Cat(const Cat &src) : Animal(src) {
    std::cout << "Cat Copy Constructor called" << std::endl;
    this->_brain = new Brain(*(src._brain)); // Yeni beyin yarat ve içindekileri kopyala!
}

Cat &Cat::operator=(const Cat &rhs) {
    std::cout << "Cat Assignment Operator called" << std::endl;
    if (this != &rhs) {
        this->_type = rhs._type;
        // Eğer zaten bir beyni varsa önce onu çöpe atıyoruz
        if (this->_brain)
            delete this->_brain;
        // Sonra rhs'nin beyninin BİREBİR KOPYASINI yeni bir RAM alanında yaratıyoruz
        this->_brain = new Brain(*(rhs._brain));
    }
    return *this;
}

Cat::~Cat() {
    delete this->_brain; // Kedi ölürken beyni de yok olmalı (Memory Leak engelleme)
    std::cout << "Cat Destructor called" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Meow! Meow!" << std::endl;
}