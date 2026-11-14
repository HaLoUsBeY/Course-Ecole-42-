#ifndef AFORM_HPP
#define AFORM_HPP

#include <string>
#include <iostream>
#include <exception>
#include "Bureaucrat.hpp"

class AForm
{
public:
    AForm();
    AForm(std::string const & name, int gradeToSign, int gradeToExecute);
    AForm(AForm const & other);
    AForm& operator=(AForm const & other);
    virtual ~AForm();

    std::string const & getName() const;
    bool getSigned() const;
    int getGradeToSign() const;
    int getGradeToExecute() const;

    void beSigned(Bureaucrat const & bureaucrat);
    void execute(Bureaucrat const & executor) const;

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

    class FormNotSignedException : public std::exception
    {
    public:
        const char* what() const throw();
    };

protected:
    // her somut form kendi işini burada yapar (saf sanal -> AForm soyut)
    virtual void executeAction() const = 0;

private:
    std::string const name_;
    bool signed_;
    int const gradeToSign_;
    int const gradeToExecute_;
};

std::ostream& operator<<(std::ostream& os, AForm const & form);

#endif
