#include "Animal.hpp"

Animal::Animal() : _type("Default_Animal") {
    std::cout << "Animal Default Constructor called" << std::endl;
}

Animal::Animal(std::string type) : _type(type) {
    std::cout << "Animal Parameterized Constructor called" << std::endl;
}

Animal::Animal(const Animal &src) {
    std::cout << "Animal Copy Constructor called" << std::endl;
    *this = src;
}

Animal &Animal::operator=(const Animal &rhs) {
    std::cout << "Animal Assignment Operator called" << std::endl;
    if (this != &rhs) {
        this->_type = rhs._type;
    }
    return *this;
}

Animal::~Animal() {
    std::cout << "Animal Destructor called" << std::endl;
}

std::string Animal::getType() const {
    return this->_type;
}