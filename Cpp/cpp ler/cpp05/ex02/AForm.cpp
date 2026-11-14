#include "AForm.hpp"

AForm::AForm() : name_("default"), signed_(false), gradeToSign_(150), gradeToExecute_(150)
{
}

AForm::AForm(std::string const & name, int gradeToSign, int gradeToExecute)
    : name_(name), signed_(false), gradeToSign_(gradeToSign), gradeToExecute_(gradeToExecute)
{
    if (gradeToSign_ < 1 || gradeToExecute_ < 1)
        throw GradeTooHighException();
    if (gradeToSign_ > 150 || gradeToExecute_ > 150)
        throw GradeTooLowException();
}

AForm::AForm(AForm const & other)
    : name_(other.name_), signed_(other.signed_),
      gradeToSign_(other.gradeToSign_), gradeToExecute_(other.gradeToExecute_)
{
}

AForm& AForm::operator=(AForm const & other)
{
    // const üyeler değiştirilemez, sadece signed_ kopyalanır
    if (this != &other)
        signed_ = other.signed_;
    return *this;
}

AForm::~AForm()
{
}

std::string const & AForm::getName() const
{
    return name_;
}

bool AForm::getSigned() const
{
    return signed_;
}

int AForm::getGradeToSign() const
{
    return gradeToSign_;
}

int AForm::getGradeToExecute() const
{
    return gradeToExecute_;
}

void AForm::beSigned(Bureaucrat const & bureaucrat)
{
    // sayı büyükse derece düşüktür
    if (bureaucrat.getGrade() > gradeToSign_)
        throw GradeTooLowException();
    signed_ = true;
}

void AForm::execute(Bureaucrat const & executor) const
{
    // kontroller tek yerde, iş alt sınıfta
    if (!signed_)
        throw FormNotSignedException();
    if (executor.getGrade() > gradeToExecute_)
        throw GradeTooLowException();
    executeAction();
}

const char* AForm::GradeTooHighException::what() const throw()
{
    return "grade is too high";
}

const char* AForm::GradeTooLowException::what() const throw()
{
    return "grade is too low";
}

const char* AForm::FormNotSignedException::what() const throw()
{
    return "form is not signed";
}

std::ostream& operator<<(std::ostream& os, AForm const & form)
{
    os << "Form " << form.getName()
       << " [signed: " << (form.getSigned() ? "yes" : "no")
       << ", grade to sign: " << form.getGradeToSign()
       << ", grade to execute: " << form.getGradeToExecute() << "]";
    return os;
}
