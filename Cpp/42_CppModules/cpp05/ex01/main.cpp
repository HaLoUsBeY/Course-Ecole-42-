#include "Bureaucrat.hpp"

int main()
{
    std::cout << "--------Test--------" << std::endl;
    {
        try
        {
            Bureaucrat a("Mükremin", 2);

            std::cout << a << std::endl;
            a.incrementGrade();
            std::cout << a << std::endl;
            a.decrementGrade();
            std::cout << a << std::endl;
        }
        catch (const Bureaucrat::GradeTooHighException& e)
        {
            std::cout << e.check() << std::endl;
        }
        catch (const Bureaucrat::GradeTooLowException& e)
        {
            std::cout << e.check() << std::endl;
        }
    }
    std::cout << "-----Wrong Test-----" << std::endl;
    {
        try
        {
            Bureaucrat a("Mükremin", 200);
            std::cout << a << std::endl;
        }
        catch (const Bureaucrat::GradeTooHighException& e)
        {
            std::cout << e.check() << std::endl;
        }
        catch (const Bureaucrat::GradeTooLowException& e)
        {
            std::cout << e.check() << std::endl;
        }
    }
    {
        try
        {
            Bureaucrat b("Mevlüt", -200);
            std::cout << b << std::endl;
        }
        catch (const Bureaucrat::GradeTooHighException& e)
        {
            std::cout << e.check() << std::endl;
        }
        catch (const Bureaucrat::GradeTooLowException& e)
        {
            std::cout << e.check() << std::endl;
        }
    }
    return 0;
}