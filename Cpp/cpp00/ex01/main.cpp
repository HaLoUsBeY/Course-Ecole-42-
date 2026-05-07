#include "PhoneBook.hpp"

int	main(void)
{
	PhoneBook phonebook;
	std::string command;

	std::cout << "Welcome to the PhoneBook!" << std::endl;
	std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl << std::endl;
	while (true)
	{
		std::cout << "Enter command: ";
		
		if (!std::getline(std::cin, command))
			break;
		
		if (command == "ADD")
		{
			phonebook.addContact();
		}
		else if (command == "SEARCH")
		{
			phonebook.searchContact();
		}
		else if (command == "EXIT")
		{
			std::cout << "Goodbye!" << std::endl;
			break;
		}
		else
		{
			std::cout << "Invalid command. Use ADD, SEARCH, or EXIT." << std::endl;
		}
		
		std::cout << std::endl;
	}

	return (0);
}
