#include "Form.hpp"

Form::Form() : name_("default"), signed_(false), gradeToSign_(150), gradeToExecute_(150)
{
}

Form::Form(std::string const & name, int gradeToSign, int gradeToExecute)
    : name_(name), signed_(false), gradeToSign_(gradeToSign), gradeToExecute_(gradeToExecute)
{
    if (gradeToSign_ < 1 || gradeToExecute_ < 1)
        throw GradeTooHighException();
    if (gradeToSign_ > 150 || gradeToExecute_ > 150)
        throw GradeTooLowException();
}

Form::Form(Form const & other)
    : name_(other.name_), signed_(other.signed_),
      gradeToSign_(other.gradeToSign_), gradeToExecute_(other.gradeToExecute_)
{
}

Form& Form::operator=(Form const & other)
{
    // const üyeler değiştirilemez, sadece signed_ kopyalanır
    if (this != &other)
        signed_ = other.signed_;
    return *this;
}

Form::~Form()
{
}

std::string const & Form::getName() const
{
    return name_;
}

bool Form::getSigned() const
{
    return signed_;
}

int Form::getGradeToSign() const
{
    return gradeToSign_;
}

int Form::getGradeToExecute() const
{
    return gradeToExecute_;
}

void Form::beSigned(Bureaucrat const & bureaucrat)
{
    // sayı büyükse derece düşüktür
    if (bureaucrat.getGrade() > gradeToSign_)
        throw GradeTooLowException();
    signed_ = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
    return "grade is too high";
}

const char* Form::GradeTooLowException::what() const throw()
{
    return "grade is too low";
}

std::ostream& operator<<(std::ostream& os, Form const & form)
{
    os << "Form " << form.getName()
       << " [signed: " << (form.getSigned() ? "yes" : "no")
       << ", grade to sign: " << form.getGradeToSign()
       << ", grade to execute: " << form.getGradeToExecute() << "]";
    return os;
}
