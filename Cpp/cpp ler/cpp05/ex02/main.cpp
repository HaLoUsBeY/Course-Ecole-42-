#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"

int main()
{
    // robotomy için rastgelelik: srand programda bir kez
    std::srand(static_cast<unsigned int>(std::time(NULL)));

    Bureaucrat boss("Boss", 1);
    Bureaucrat manager("Manager", 50);
    Bureaucrat clerk("Clerk", 140);

    std::cout << "--- test: bureaucrats ---" << std::endl;
    std::cout << boss << std::endl;
    std::cout << manager << std::endl;
    std::cout << clerk << std::endl;

    // AForm form; // derlenmez: AForm soyut bir sınıf

    std::cout << std::endl << "--- test: ShrubberyCreationForm (sign 145, exec 137) ---" << std::endl;
    {
        ShrubberyCreationForm shrub("home");

        std::cout << shrub << std::endl;
        clerk.executeForm(shrub);
        clerk.signForm(shrub);
        clerk.executeForm(shrub);
        manager.executeForm(shrub);
    }

    std::cout << std::endl << "--- test: ShrubberyCreationForm file cannot be opened ---" << std::endl;
    {
        ShrubberyCreationForm badShrub("no_such_dir/home");

        boss.signForm(badShrub);
        boss.executeForm(badShrub);
    }

    std::cout << std::endl << "--- test: RobotomyRequestForm (sign 72, exec 45) ---" << std::endl;
    {
        RobotomyRequestForm robot("Bender");

        std::cout << robot << std::endl;
        clerk.signForm(robot);
        manager.signForm(robot);
        manager.executeForm(robot);
        for (int i = 0; i < 4; i++)
            boss.executeForm(robot);
    }

    std::cout << std::endl << "--- test: PresidentialPardonForm (sign 25, exec 5) ---" << std::endl;
    {
        PresidentialPardonForm pardon("Arthur Dent");

        std::cout << pardon << std::endl;
        manager.signForm(pardon);
        boss.signForm(pardon);
        manager.executeForm(pardon);
        boss.executeForm(pardon);
    }

    std::cout << std::endl << "--- test: execute() directly with try/catch ---" << std::endl;
    {
        PresidentialPardonForm pardon("Ford Prefect");

        try
        {
            pardon.execute(boss);
            std::cout << "this line must not be printed" << std::endl;
        }
        catch (AForm::FormNotSignedException & e)
        {
            std::cout << "Caught AForm::FormNotSignedException: " << e.what() << std::endl;
        }
        boss.signForm(pardon);
        try
        {
            pardon.execute(manager);
            std::cout << "this line must not be printed" << std::endl;
        }
        catch (std::exception & e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
        }
    }

    std::cout << std::endl << "--- test: polymorphism through AForm pointers ---" << std::endl;
    {
        AForm* forms[3];

        forms[0] = new ShrubberyCreationForm("garden");
        forms[1] = new RobotomyRequestForm("Marvin");
        forms[2] = new PresidentialPardonForm("Trillian");
        for (int i = 0; i < 3; i++)
        {
            boss.signForm(*forms[i]);
            boss.executeForm(*forms[i]);
            std::cout << *forms[i] << std::endl;
        }
        // sanal yıkıcı sayesinde alt sınıfın yıkıcısı da çağrılır
        for (int i = 0; i < 3; i++)
            delete forms[i];
    }

    std::cout << std::endl << "--- test: copy constructor and assignment ---" << std::endl;
    {
        PresidentialPardonForm original("Zaphod");
        boss.signForm(original);

        PresidentialPardonForm copy(original);
        PresidentialPardonForm assigned;
        assigned = original;

        std::cout << "copy:     " << copy << ", target: " << copy.getTarget() << std::endl;
        std::cout << "assigned: " << assigned << ", target: " << assigned.getTarget() << std::endl;
    }
    return 0;
}
