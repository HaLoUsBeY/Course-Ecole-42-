#include "PhoneBook.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>

PhoneBook::PhoneBook(void)
	: _index(0)
{
	std::cout<<"Ben oluştum PhoneBook"<< std::endl;
}

PhoneBook::~PhoneBook(void)
{
		std::cout<<"Ben  bittim  PhoneBook"<< std::endl;

}

void	PhoneBook::addContact(void)
{
	Contact contact;
	
	if (contact.setContact())
	{
		this->_contacts[this->_index] = contact;
		this->_index = (this->_index + 1) % 8;
		std::cout << "Contact added successfully!" << std::endl;
	}
	else
	{
		std::cout << "Error: Failed to add contact." << std::endl;
	}
}

void	PhoneBook::displayContactList(void) const
{
	std::cout << std::setw(10) << "Index" << "|"
			  << std::setw(10) << "First Name" << "|"
			  << std::setw(10) << "Last Name" << "|"
			  << std::setw(10) << "Nickname" << std::endl;
	
	for (int i = 0; i < 8; i++)
	{
		std::string firstName = this->_contacts[i].getFirstName();
		if (firstName.empty())
			continue;
		
		std::string lastName = this->_contacts[i].getLastName();
		std::string nickname = this->_contacts[i].getNickname();
		
		// Fazla uzun ise kısalt
		if (firstName.length() > 9)
			firstName = firstName.substr(0, 8) + ".";
		if (lastName.length() > 9)
			lastName = lastName.substr(0, 8) + ".";
		if (nickname.length() > 9)
			nickname = nickname.substr(0, 8) + ".";
		
		std::cout << std::setw(10) << i << "|"
				  << std::setw(10) << firstName << "|"
				  << std::setw(10) << lastName << "|"
				  << std::setw(10) << nickname << std::endl;
	}
}

void	PhoneBook::searchContact(void) const
{
	this->displayContactList();
	
	std::cout << "Enter the index of the contact: ";
	std::string input;
	
	if (!std::getline(std::cin, input))
		return;
	
	std::stringstream ss(input);
	int index;
	
	if (!(ss >> index) || index < 0 || index > 7)
	{
		std::cout << "Invalid index!" << std::endl;
		return;
	}
	
	std::string firstName = this->_contacts[index].getFirstName();
	if (firstName.empty())
	{
		std::cout << "Contact not found!" << std::endl;
		return;
	}
	
	this->_contacts[index].displayContact();
}
