#include "Contact.hpp"
#include <cctype>

Contact::Contact(void)
	: _firstName(""), _lastName(""), _nickname(""), _phoneNumber(""), _darkestSecret("")
{
		std::cout<<"Ben oluiştum Contact"<< std::endl;

}

Contact::~Contact(void)
{
		std::cout<<"Ben bittim Contact"<< std::endl;
}

bool Contact::setContact(void)
{
	std::cout << "Enter first name: ";
	if (!std::getline(std::cin, this->_firstName))
		return (false);
	
	std::cout << "Enter last name: ";
	if (!std::getline(std::cin, this->_lastName))
		return (false);
	
	std::cout << "Enter nickname: ";
	if (!std::getline(std::cin, this->_nickname))
		return (false);
	
	std::cout << "Enter phone number: ";
	if (!std::getline(std::cin, this->_phoneNumber))
		return (false);
	
	// Telefon numarası sadece rakam olmalı (ama boş olabilir)
	for (size_t i = 0; i < this->_phoneNumber.length(); i++)
	{
		if (!isdigit(this->_phoneNumber[i]))
		{
			std::cout << "Error: Phone number must contain only digits!" << std::endl;
			return (false);
		}
	}
	
	std::cout << "Enter darkest secret: ";
	if (!std::getline(std::cin, this->_darkestSecret))
		return (false);
	
	return (true);
}

std::string	Contact::getFirstName(void) const
{
	return (this->_firstName);
}

std::string	Contact::getLastName(void) const
{
	return (this->_lastName);
}

std::string	Contact::getNickname(void) const
{
	return (this->_nickname);
}

std::string	Contact::getPhoneNumber(void) const
{
	return (this->_phoneNumber);
}

std::string	Contact::getDarkestSecret(void) const
{
	return (this->_darkestSecret);
}


void	Contact::displayContact(void) const
{
	std::cout << "First name: " << this->_firstName << std::endl;
	std::cout << "Last name: " << this->_lastName << std::endl;
	std::cout << "Nickname: " << this->_nickname << std::endl;
	std::cout << "Phone number: " << this->_phoneNumber << std::endl;
	std::cout << "Darkest secret: " << this->_darkestSecret << std::endl;
}

