#include "PhoneBook.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <cctype>

PhoneBook::PhoneBook() : index(0), total(0) {}

std::string PhoneBook::formatField(std::string str)
{
    if (str.length() > 10)
        return str.substr(0, 9) + ".";
    return str;
}

bool PhoneBook::addContact(void)
{
    if (!contacts[index].setContact())
        return false;
    index = (index + 1) % 8;
    if (total < 8)
        total++;
    return true;
}

bool PhoneBook::searchContact(void)
{
    if (total == 0)
    {
        std::cout << "PhoneBook is empty. Please add a contact first." << std::endl;
        return 1;
    }
    std::cout << std::setw(10) << std::right << "Index" << "|"
              << std::setw(10) << std::right << "First Name" << "|"
              << std::setw(10) << std::right << "Last Name" << "|"
              << std::setw(10) << std::right << "Nickname" << std::endl;
    for (int i = 0; i < total; i++)
    {
        std::cout << std::setw(10) << std::right << i + 1 << "|"
                  << std::setw(10) << std::right << formatField(contacts[i].getFirstName()) << "|"
                  << std::setw(10) << std::right << formatField(contacts[i].getLastName()) << "|"
                  << std::setw(10) << std::right << formatField(contacts[i].getNickname()) << std::endl;
    }

    std::string input;
    int index;

    while (true)
    {
        std::cout << "Enter the index of the contact to view details (1-" << total << "): ";
        if(!std::getline(std::cin, input))
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            return 0;
        }
        if (std::cin.eof())
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting search." << std::endl;
            return 0;
        }
        if (input.length() == 1 && std::isdigit(input[0]))
        {
            index = input[0] - '0';
            if (index >= 1 && index <= total)
            {
                displayContact(index - 1);
                return 1;
            }
        }
        std::cout << "Invalid index." << std::endl;
    }
}

void PhoneBook::displayContact(int i)
{
    if (i < 0 || i >= total)
    {
        std::cout << "Invalid contact index." << std::endl;
        return;
    }
    std::cout << "First Name: " << contacts[i].getFirstName() << std::endl;
    std::cout << "Last Name: " << contacts[i].getLastName() << std::endl;
    std::cout << "Nickname: " << contacts[i].getNickname() << std::endl;
    std::cout << "Phone Number: " << contacts[i].getPhoneNumber() << std::endl;
    std::cout << "Darkest Secret: " << contacts[i].getDarkestSecret() << std::endl;
}