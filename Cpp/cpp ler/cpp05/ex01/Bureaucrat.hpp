#ifndef BUREAUCRAT_HPP
#define BUREAUCRAT_HPP

#include <string>
#include <iostream>
#include <exception>

// Form.hpp bu dosyayı include ettiği için burada sadece ileri bildirim
class Form;

class Bureaucrat
{
public:
    Bureaucrat();
    Bureaucrat(std::string const & name, int grade);
    Bureaucrat(Bureaucrat const & other);
    Bureaucrat& operator=(Bureaucrat const & other);
    ~Bureaucrat();

    std::string const & getName() const;
    int getGrade() const;

    void incrementGrade();
    void decrementGrade();

    void signForm(Form & form) const;

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
    int grade_;
};

std::ostream& operator<<(std::ostream& os, Bureaucrat const & bureaucrat);

#endif
