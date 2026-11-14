#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
    std::cout << "--- test: form construction ---" << std::endl;
    try
    {
        Form taxForm("TaxForm", 50, 25);
        std::cout << taxForm << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << std::endl << "--- test: form with sign grade 0 ---" << std::endl;
    try
    {
        Form bad("BadForm", 0, 10);
        std::cout << "this line must not be printed" << std::endl;
    }
    catch (Form::GradeTooHighException & e)
    {
        std::cout << "Caught Form::GradeTooHighException: " << e.what() << std::endl;
    }

    std::cout << std::endl << "--- test: form with execute grade 151 ---" << std::endl;
    try
    {
        Form bad("BadForm", 10, 151);
        std::cout << "this line must not be printed" << std::endl;
    }
    catch (Form::GradeTooLowException & e)
    {
        std::cout << "Caught Form::GradeTooLowException: " << e.what() << std::endl;
    }

    std::cout << std::endl << "--- test: successful signing ---" << std::endl;
    {
        Bureaucrat boss("Boss", 1);
        Form contract("Contract", 20, 10);

        std::cout << contract << std::endl;
        boss.signForm(contract);
        std::cout << contract << std::endl;
    }

    std::cout << std::endl << "--- test: grade equal to required grade ---" << std::endl;
    {
        Bureaucrat manager("Manager", 50);
        Form request("Request", 50, 50);

        manager.signForm(request);
        std::cout << request << std::endl;
    }

    std::cout << std::endl << "--- test: failed signing (grade too low) ---" << std::endl;
    {
        Bureaucrat clerk("Clerk", 140);
        Form secret("SecretForm", 20, 10);

        clerk.signForm(secret);
        std::cout << secret << std::endl;
    }

    std::cout << std::endl << "--- test: beSigned called directly ---" << std::endl;
    {
        Bureaucrat clerk("Clerk", 100);
        Form permit("Permit", 99, 99);

        try
        {
            permit.beSigned(clerk);
            std::cout << "this line must not be printed" << std::endl;
        }
        catch (std::exception & e)
        {
            std::cout << "Exception: " << e.what() << std::endl;
        }
        clerk.incrementGrade();
        permit.beSigned(clerk);
        std::cout << "after increment: " << permit << std::endl;
    }

    std::cout << std::endl << "--- test: copy constructor and assignment ---" << std::endl;
    {
        Bureaucrat boss("Boss", 1);
        Form original("Original", 30, 40);
        boss.signForm(original);

        Form copy(original);
        Form assigned;
        assigned = original;

        std::cout << "original: " << original << std::endl;
        std::cout << "copy:     " << copy << std::endl;
        std::cout << "assigned: " << assigned << " (const parts not copied)" << std::endl;
    }
    return 0;
}
