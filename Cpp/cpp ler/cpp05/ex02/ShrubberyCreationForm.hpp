#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP

#include <string>
#include <exception>
#include "AForm.hpp"

class ShrubberyCreationForm : public AForm
{
public:
    ShrubberyCreationForm();
    ShrubberyCreationForm(std::string const & target);
    ShrubberyCreationForm(ShrubberyCreationForm const & other);
    ShrubberyCreationForm& operator=(ShrubberyCreationForm const & other);
    ~ShrubberyCreationForm();

    std::string const & getTarget() const;

    class FileOpenException : public std::exception
    {
    public:
        const char* what() const throw();
    };

protected:
    void executeAction() const;

private:
    std::string target_;
};

#endif
