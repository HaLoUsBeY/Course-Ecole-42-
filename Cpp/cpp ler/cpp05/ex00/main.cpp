#include "Bureaucrat.hpp"

int main()
{
    std::cout << "--- test: normal construction ---" << std::endl;
    try
    {
        Bureaucrat alice("Alice", 42);
        std::cout << alice << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << std::endl << "--- test: increment and decrement ---" << std::endl;
    try
    {
        Bureaucrat bob("Bob", 3);
        std::cout << bob << std::endl;
        bob.incrementGrade();
        std::cout << "after increment: " << bob << std::endl;
        bob.decrementGrade();
        bob.decrementGrade();
        std::cout << "after 2 decrements: " << bob << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << std::endl << "--- test: construction with grade 0 ---" << std::endl;
    try
    {
        Bureaucrat tooHigh("TooHigh", 0);
        std::cout << "this line must not be printed" << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }

    std::cout << std::endl << "--- test: construction with grade 151 ---" << std::endl;
    try
    {
        Bureaucrat tooLow("TooLow", 151);
        std::cout << "this line must not be printed" << std::endl;
    }
    catch (Bureaucrat::GradeTooLowException & e)
    {
        std::cout << "Caught Bureaucrat::GradeTooLowException: " << e.what() << std::endl;
    }

    std::cout << std::endl << "--- test: increment at grade 1 ---" << std::endl;
    Bureaucrat top("Top", 1);
    try
    {
        top.incrementGrade();
        std::cout << "this line must not be printed" << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << "grade unchanged: " << top << std::endl;

    std::cout << std::endl << "--- test: decrement at grade 150 ---" << std::endl;
    Bureaucrat bottom("Bottom", 150);
    try
    {
        bottom.decrementGrade();
        std::cout << "this line must not be printed" << std::endl;
    }
    catch (std::exception & e)
    {
        std::cout << "Exception: " << e.what() << std::endl;
    }
    std::cout << "grade unchanged: " << bottom << std::endl;

    std::cout << std::endl << "--- test: copy constructor and assignment ---" << std::endl;
    {
        Bureaucrat original("Original", 75);
        Bureaucrat copy(original);
        Bureaucrat assigned;

        std::cout << "before assignment: " << assigned << std::endl;
        assigned = original;
        std::cout << "original: " << original << std::endl;
        std::cout << "copy:     " << copy << std::endl;
        std::cout << "assigned: " << assigned << " (name is const, only grade copied)" << std::endl;
    }
    return 0;
}
