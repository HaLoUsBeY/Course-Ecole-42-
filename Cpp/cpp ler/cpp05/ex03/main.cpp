#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstddef>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"

int main()
{
    // robotomy için rastgelelik: srand programda bir kez
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    Intern someRandomIntern;
    Bureaucrat boss("Boss", 1);
    Bureaucrat clerk("Clerk", 140);

    std::cout << "--- test: example from the subject ---" << std::endl;
    {
        AForm* rrf;

        rrf = someRandomIntern.makeForm("robotomy request", "Bender");
        if (rrf != NULL)
        {
            std::cout << *rrf << std::endl;
            boss.signForm(*rrf);
            boss.executeForm(*rrf);
            delete rrf;
        }
    }

    std::cout << std::endl << "--- test: all known forms ---" << std::endl;
    {
        AForm* forms[3];

        forms[0] = someRandomIntern.makeForm("shrubbery creation", "office");
        forms[1] = someRandomIntern.makeForm("robotomy request", "Marvin");
        forms[2] = someRandomIntern.makeForm("presidential pardon", "Arthur Dent");
        for (int i = 0; i < 3; i++)
        {
            if (forms[i] == NULL)
                continue;
            clerk.signForm(*forms[i]);
            boss.signForm(*forms[i]);
            clerk.executeForm(*forms[i]);
            boss.executeForm(*forms[i]);
        }
        for (int i = 0; i < 3; i++)
            delete forms[i];
    }

    std::cout << std::endl << "--- test: unknown form names ---" << std::endl;
    {
        AForm* unknown = someRandomIntern.makeForm("coffee making", "kitchen");
        if (unknown == NULL)
            std::cout << "makeForm returned NULL" << std::endl;

        // büyük/küçük harf farkı da bilinmeyen sayılır
        AForm* wrongCase = someRandomIntern.makeForm("Robotomy Request", "Bender");
        if (wrongCase == NULL)
            std::cout << "makeForm returned NULL" << std::endl;
    }

    std::cout << std::endl << "--- test: Intern copy and assignment ---" << std::endl;
    {
        Intern copy(someRandomIntern);
        Intern assigned;
        assigned = copy;

        AForm* form = assigned.makeForm("presidential pardon", "Ford Prefect");
        if (form != NULL)
        {
            std::cout << *form << std::endl;
            delete form;
        }
    }
    return 0;
}
