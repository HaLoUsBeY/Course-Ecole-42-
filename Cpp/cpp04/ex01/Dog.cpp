#include "Dog.hpp"

Dog::Dog() : Animal() {
    this->_type = "Dog";
    this->_brain = new Brain();
    std::cout << "Dog Default Constructor called" << std::endl;
}

Dog::Dog(const Dog &src) : Animal(src) {
    std::cout << "Dog Copy Constructor called" << std::endl;
    this->_brain = new Brain(*(src._brain));
}

Dog &Dog::operator=(const Dog &rhs) {
    std::cout << "Dog Assignment Operator called" << std::endl;
    if (this != &rhs) {
        this->_type = rhs._type;
        if (this->_brain)
            delete this->_brain;
        this->_brain = new Brain(*(rhs._brain));
    }
    return *this;
}

Dog::~Dog() {
    delete this->_brain;
    std::cout << "Dog Destructor called" << std::endl;
}

void Dog::makeSound() const {
    std::cout << "Woof! Woof!" << std::endl;
}