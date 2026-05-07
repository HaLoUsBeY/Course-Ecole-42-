#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name("unknow"), grade(150) {}

Bureaucrat::Bureaucrat(const std::string& name, int grade) : name(name)
{
	if(grade < 1)
		throw Bureaucrat::GradeTooHighException();
	if(grade > 150)
		throw Bureaucrat::GradeTooLowException();
	this->grade = grade;
}

Bureaucrat::Bureaucrat(const Bureaucrat& copy) : name(copy.name) {this->grade = copy.grade;}

Bureaucrat& Bureaucrat::operator=(const Bureaucrat& copy) 
{
	if(this != &copy)
		this->grade = copy.grade;
	return *this;
}

Bureaucrat::~Bureaucrat() {}
std::string Bureaucrat::getName() const {return name;}
int Bureaucrat::getGrade() const {return grade;}

void Bureaucrat::incrementGrade()
{
	if (grade <= 1)
		throw GradeTooHighException();
	grade --;
}

void Bureaucrat::decrementGrade()
{
	if (grade >= 150)
		throw GradeTooLowException();
	grade ++;
}

const char* Bureaucrat::GradeTooHighException::check() const throw() {
    return "Grade is too high! (Limit: 1)";
}

const char* Bureaucrat::GradeTooLowException::check() const throw() {
    return "Grade is too low!  (Limit: 150)";
}

std::ostream &operator<<(std::ostream &out, Bureaucrat const &right) {
	out << right.getName() << ", bureaucrat grade " << right.getGrade();
	return (out);
}