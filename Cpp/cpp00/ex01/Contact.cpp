#include "Contact.hpp"

Contact::Contact(void)
{
    this->_firstName = "";
    this->_lastName = "";
    this->_nickname = "";
    this->_phoneNumber = "";
    this->_darkestSecret = "";
}

Contact::~Contact(void){}

bool Contact::setContact(void)
{
	std::cout << "Enter first name: ";
	if (!std::getline(std::cin, this->_firstName))
		return (false);
	if (this->_firstName.empty())
	{
		std::cout << "Error: First name is required!" << std::endl;
		return (false);
	}
	
	std::cout << "Enter last name (optional, press Enter to skip): ";
	std::getline(std::cin, this->_lastName);
	
	std::cout << "Enter nickname (optional, press Enter to skip): ";
	std::getline(std::cin, this->_nickname);
	
	std::cout << "Enter phone number: ";
	if (!std::getline(std::cin, this->_phoneNumber))
		return (false);
	if (this->_phoneNumber.empty())
	{
		std::cout << "Error: Phone number is required!" << std::endl;
		return (false);
	}
	
	for (size_t i = 0; i < this->_phoneNumber.length(); i++)
	{
		if (!std::isdigit(this->_phoneNumber[i]))
		{
			std::cout << "Error: Phone number must contain only digits!" << std::endl;
			return (false);
		}
	}
	
	std::cout << "Enter darkest secret (optional, press Enter to skip): ";
	std::getline(std::cin, this->_darkestSecret);
	
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

