#ifndef FORM_HPP
#define FORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class Form
{
public:
    Form();
    Form(std::string const & name, int gradeToSign, int gradeToExecute);
    Form(Form const & other);
    Form& operator=(Form const & other);
    ~Form();

    std::string const & getName() const;
    bool getSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;

    void beSigned(Bureaucrat const & bureaucrat);

    class GradeTooHighException : public std::exception
    {
    public:
        const char* what() const throw();
    };

    class GradeTooLowException : public std::exception
    {
    public:
        const char* what() const throw();
    };

private:
    std::string const name_;
    bool signed_;
    int const gradeToSign_;
    int const gradeToExecute_;
};

std::ostream& operator<<(std::ostream& os, Form const & form);

#endif
