#include "Cat.hpp"

Cat::Cat() : Animal("Cat") {
    std::cout << "Cat Default Constructor called" << std::endl;
}

Cat::Cat(const Cat &src) : Animal(src) {
    std::cout << "Cat Copy Constructor called" << std::endl;
    *this = src;
}

Cat &Cat::operator=(const Cat &rhs) {
    std::cout << "Cat Assignment Operator called" << std::endl;
    if (this != &rhs) {
        this->_type = rhs._type;
    }
    return *this;
}

Cat::~Cat() {
    std::cout << "Cat Destructor called" << std::endl;
}

void Cat::makeSound() const {
    std::cout << "Meow! Meow! Purr..." << std::endl;
}