#include "PhoneBook.hpp"
#include <iostream>

int main()
{
    PhoneBook phoneBook;
    std::string command;

    std::cout << "Available commands: ADD, SEARCH, EXIT" << std::endl;

    while (true)
    {
        std::cout << "Enter command: ";
        if(!std::getline(std::cin, command))
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            break;
        }
        if (std::cin.eof())
        {
            std::cin.clear();
            std::cout << "\nEOF detected. Exiting program." << std::endl;
            break;
        }
        if (command == "ADD")
        {
            if (!phoneBook.addContact())
                break;
        }
        else if (command == "SEARCH")
        {
            if (!phoneBook.searchContact())
                break;
        }
        else if (command == "EXIT")
        {
            std::cout << "Exiting PhoneBook." << std::endl;
            break;
        }
        else
            std::cout << "Invalid command. Please enter ADD, SEARCH, or EXIT." << std::endl;
    }
    return (0);
}