#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
private:
	Contact	_contacts[8];
	int		_index;

public:
	PhoneBook(void);
	~PhoneBook(void);

	void	addContact(void);
	void	searchContact(void) const;
	void	displayContactList(void) const;

private:
	std::string	_getInput(std::string prompt) const;
	void		_displayContactPreview(int contactIndex) const;
	int			_getUserChoice(int maxIndex) const;
};

#endif
