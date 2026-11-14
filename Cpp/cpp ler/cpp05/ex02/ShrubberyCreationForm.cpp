#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
    : AForm("ShrubberyCreationForm", 145, 137), target_("default")
{
}

ShrubberyCreationForm::ShrubberyCreationForm(std::string const & target)
    : AForm("ShrubberyCreationForm", 145, 137), target_(target)
{
}

ShrubberyCreationForm::ShrubberyCreationForm(ShrubberyCreationForm const & other)
    : AForm(other), target_(other.target_)
{
}

ShrubberyCreationForm& ShrubberyCreationForm::operator=(ShrubberyCreationForm const & other)
{
    if (this != &other)
    {
        AForm::operator=(other);
        target_ = other.target_;
    }
    return *this;
}

ShrubberyCreationForm::~ShrubberyCreationForm()
{
}

std::string const & ShrubberyCreationForm::getTarget() const
{
    return target_;
}

void ShrubberyCreationForm::executeAction() const
{
    std::string const fileName = target_ + "_shrubbery";
    // C++98'de ofstream std::string almaz, c_str() gerekir
    std::ofstream file(fileName.c_str());

    if (!file.is_open())
        throw FileOpenException();

    for (int i = 0; i < 2; i++)
    {
        file << "        #" << std::endl;
        file << "       ###" << std::endl;
        file << "      #####" << std::endl;
        file << "     #######" << std::endl;
        file << "    #########" << std::endl;
        file << "   ###########" << std::endl;
        file << "  #############" << std::endl;
        file << "       | |" << std::endl;
        file << "       | |" << std::endl;
        file << std::endl;
    }
    file.close();
}

const char* ShrubberyCreationForm::FileOpenException::what() const throw()
{
    return "could not open the shrubbery file";
}
