#include "Intern.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
#include <cstddef>

// form oluşturan fonksiyonların ortak tipi: hedefi alır, AForm* döner
typedef AForm* (*FormCreator)(std::string const & target);

static AForm* createShrubbery(std::string const & target)
{
    return new ShrubberyCreationForm(target);
}

static AForm* createRobotomy(std::string const & target)
{
    return new RobotomyRequestForm(target);
}

static AForm* createPardon(std::string const & target)
{
    return new PresidentialPardonForm(target);
}

Intern::Intern()
{
}

Intern::Intern(Intern const & other)
{
    (void)other;
}

Intern& Intern::operator=(Intern const & other)
{
    // kopyalanacak üye yok
    (void)other;
    return *this;
}

Intern::~Intern()
{
}

AForm* Intern::makeForm(std::string const & formName, std::string const & target) const
{
    // isimler ve oluşturucular aynı sırada: names[i] <-> creators[i]
    std::string const names[3] = {"shrubbery creation", "robotomy request", "presidential pardon"};
    FormCreator const creators[3] = {&createShrubbery, &createRobotomy, &createPardon};

    for (int i = 0; i < 3; i++)
    {
        if (formName == names[i])
        {
            AForm* form = creators[i](target);
            std::cout << "Intern creates " << form->getName() << std::endl;
            return form;
        }
    }
    std::cout << "Intern couldn't create \"" << formName
              << "\": no such form exists." << std::endl;
    return NULL;
}
