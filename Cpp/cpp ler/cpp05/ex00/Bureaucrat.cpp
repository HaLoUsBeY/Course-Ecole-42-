#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : name_("default"), grade_(150)
{
}

Bureaucrat::Bureaucrat(std::string const & name, int grade) : name_(name), grade_(grade)
{
    // 1 en yüksek, 150 en düşük derece
    if (grade_ < 1)
        throw GradeTooHighException();
    if (grade_ > 150)
        throw GradeTooLowException();
}

Bureaucrat::Bureaucrat(Bureaucrat const & other) : name_(other.name_), grade_(other.grade_)
{
}

Bureaucrat& Bureaucrat::operator=(Bureaucrat const & other)
{
    // name_ const olduğu için sadece grade_ kopyalanır
    if (this != &other)
        grade_ = other.grade_;
    return *this;
}

Bureaucrat::~Bureaucrat()
{
}

std::string const & Bureaucrat::getName() const
{
    return name_;
}

int Bureaucrat::getGrade() const
{
    return grade_;
}

void Bureaucrat::incrementGrade()
{
    // derece artırmak = sayıyı küçültmek (3 -> 2)
    if (grade_ - 1 < 1)
        throw GradeTooHighException();
    grade_--;
}

void Bureaucrat::decrementGrade()
{
    if (grade_ + 1 > 150)
        throw GradeTooLowException();
    grade_++;
}

const char* Bureaucrat::GradeTooHighException::what() const throw()
{
    return "grade is too high";
}

const char* Bureaucrat::GradeTooLowException::what() const throw()
{
    return "grade is too low";
}

std::ostream& operator<<(std::ostream& os, Bureaucrat const & bureaucrat)
{
    os << bureaucrat.getName() << ", bureaucrat grade " << bureaucrat.getGrade() << ".";
    return os;
}
