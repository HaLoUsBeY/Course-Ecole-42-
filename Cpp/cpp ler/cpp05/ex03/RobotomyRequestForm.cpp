#include "RobotomyRequestForm.hpp"
#include <iostream>
#include <cstdlib>

RobotomyRequestForm::RobotomyRequestForm()
    : AForm("RobotomyRequestForm", 72, 45), target_("default")
{
}

RobotomyRequestForm::RobotomyRequestForm(std::string const & target)
    : AForm("RobotomyRequestForm", 72, 45), target_(target)
{
}

RobotomyRequestForm::RobotomyRequestForm(RobotomyRequestForm const & other)
    : AForm(other), target_(other.target_)
{
}

RobotomyRequestForm& RobotomyRequestForm::operator=(RobotomyRequestForm const & other)
{
    if (this != &other)
    {
        AForm::operator=(other);
        target_ = other.target_;
    }
    return *this;
}

RobotomyRequestForm::~RobotomyRequestForm()
{
}

std::string const & RobotomyRequestForm::getTarget() const
{
    return target_;
}

void RobotomyRequestForm::executeAction() const
{
    std::cout << "* BZZZZZZ... DRRRRRRR... VRRRRRR... *" << std::endl;
    // srand main'de bir kez çağrılır; rand() % 2 -> %50
    if (std::rand() % 2 == 0)
        std::cout << target_ << " has been robotomized successfully." << std::endl;
    else
        std::cout << "The robotomy of " << target_ << " failed." << std::endl;
}
