#include "Harl.hpp"

int main() {
    Harl grumpyHarl;

    std::cout << "--- HARL IS ENTERING THE RESTAURANT ---\n" << std::endl;

    grumpyHarl.complain("DEBUG");
    grumpyHarl.complain("INFO");
    grumpyHarl.complain("WARNING");
    grumpyHarl.complain("ERROR");

    std::cout << "--- HARL IS TRYING TO COMPLAIN ABOUT THE WEATHER ---\n" << std::endl;
    grumpyHarl.complain("IT'S TOO HOT");

    return 0;
}