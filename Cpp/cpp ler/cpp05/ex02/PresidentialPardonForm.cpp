#include "PresidentialPardonForm.hpp"
#include <iostream>

PresidentialPardonForm::PresidentialPardonForm()
    : AForm("PresidentialPardonForm", 25, 5), target_("default")
{
}

PresidentialPardonForm::PresidentialPardonForm(std::string const & target)
    : AForm("PresidentialPardonForm", 25, 5), target_(target)
{
}

PresidentialPardonForm::PresidentialPardonForm(PresidentialPardonForm const & other)
    : AForm(other), target_(other.target_)
{
}

PresidentialPardonForm& PresidentialPardonForm::operator=(PresidentialPardonForm const & other)
{
    if (this != &other)
    {
        AForm::operator=(other);
        target_ = other.target_;
    }
    return *this;
}

PresidentialPardonForm::~PresidentialPardonForm()
{
}

std::string const & PresidentialPardonForm::getTarget() const
{
    return target_;
}

void PresidentialPardonForm::executeAction() const
{
    std::cout << target_ << " has been pardoned by Zaphod Beeblebrox." << std::endl;
}
