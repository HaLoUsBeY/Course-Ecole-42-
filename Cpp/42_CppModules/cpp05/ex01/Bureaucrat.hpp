#pragma once

#include <iostream>
#include <exception>

class Bureaucrat
{
private:
	const std::string name;
	int grade;
public:
	Bureaucrat();
	Bureaucrat(const std::string& name, int grade);
	Bureaucrat(const Bureaucrat& copy);
	Bureaucrat &operator=(const Bureaucrat& copy);
	~Bureaucrat();

	int getGrade() const;
	std::string getName() const;

	void incrementGrade();
    void decrementGrade();

	class GradeTooHighException : public std::exception
	{
	public:
		const char* check() const throw();
	};

	class GradeTooLowException : public std::exception
	{
	public:
		const char* check() const throw();
	};
};

std::ostream &operator<<(std::ostream &out, const Bureaucrat &right);