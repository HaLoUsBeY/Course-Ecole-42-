#ifndef PRESIDENTIALPARDONFORM_HPP
#define PRESIDENTIALPARDONFORM_HPP

#include <string>
#include "AForm.hpp"

class PresidentialPardonForm : public AForm
{
public:
    PresidentialPardonForm();
    PresidentialPardonForm(std::string const & target);
    PresidentialPardonForm(PresidentialPardonForm const & other);
    PresidentialPardonForm& operator=(PresidentialPardonForm const & other);
    ~PresidentialPardonForm();

    std::string const & getTarget() const;

protected:
    void executeAction() const;

private:
    std::string target_;
};

#endif
