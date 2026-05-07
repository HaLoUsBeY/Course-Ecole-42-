#include "Contact.hpp"
#include <iostream>

Contact::Contact() {}
bool Contact::setContact(void)
{
    do {
        std::cout << "Enter first name: ";
        if (!std::getline(std::cin, first_name))
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (std::cin.eof())
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (first_name.empty())
            std::cout << "First name cannot be empty." << std::endl;
    } while (first_name.empty());

    do {
        std::cout << "Enter last name: ";
        if (!std::getline(std::cin, last_name))
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (std::cin.eof())
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (last_name.empty())
            std::cout << "Last name cannot be empty." << std::endl;
    } while (last_name.empty());

    do {
        std::cout << "Enter nickname: ";
         if (!std::getline(std::cin, nickname))
        {
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (std::cin.eof())
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (nickname.empty())
            std::cout << "Nickname cannot be empty." << std::endl;
    } while (nickname.empty());

    do {
        std::cout << "Enter phone number: ";
        if (!std::getline(std::cin, phone_number))
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (std::cin.eof())
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (phone_number.empty())
            std::cout << "Phone number cannot be empty." << std::endl;
    } while (phone_number.empty());

    do {
        std::cout << "Enter darkest secret: ";
        if (!std::getline(std::cin, darkest_secret))
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (std::cin.eof())
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return false;
        }
        if (darkest_secret.empty())
            std::cout << "Darkest secret cannot be empty." << std::endl;
    } while (darkest_secret.empty());
    return true;
}

std::string Contact::getFirstName(void) { return first_name; }
std::string Contact::getLastName(void) { return last_name; }
std::string Contact::getNickname(void)  { return nickname; }
std::string Contact::getPhoneNumber(void) { return phone_number; }
std::string Contact::getDarkestSecret(void) { return darkest_secret; }