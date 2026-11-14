#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP

#include <string>
#include "AForm.hpp"

class RobotomyRequestForm : public AForm
{
public:
    RobotomyRequestForm();
    RobotomyRequestForm(std::string const & target);
    RobotomyRequestForm(RobotomyRequestForm const & other);
    RobotomyRequestForm& operator=(RobotomyRequestForm const & other);
    ~RobotomyRequestForm();

    std::string const & getTarget() const;

protected:
    void executeAction() const;

private:
    std::string target_;
};

#endif
