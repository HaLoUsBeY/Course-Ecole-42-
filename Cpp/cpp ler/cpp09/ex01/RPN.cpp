#include "RPN.hpp"

#include <climits>
#include <sstream>
#include <stdexcept>

RPN::RPN()
{
}

RPN::RPN(const RPN &other) : stack_(other.stack_)
{
}

RPN &RPN::operator=(const RPN &other)
{
    if (this != &other)
        stack_ = other.stack_;
    return *this;
}

RPN::~RPN()
{
}

// Örnek: "3 4 + 2 *" -> 3 ve 4 yığına, '+' ikisini alıp 7 koyar, ... sonuç 14
long RPN::evaluate(const std::string &expression)
{
    while (!stack_.empty())
        stack_.pop();

    std::istringstream iss(expression);
    std::string token;
    while (iss >> token)
    {
        if (token.size() != 1)
            throw std::runtime_error("Error");

        char c = token[0];
        if (c >= '0' && c <= '9')
            stack_.push(c - '0');
        else if (c == '+' || c == '-' || c == '*' || c == '/')
            applyOperator(c);
        else
            throw std::runtime_error("Error");
    }

    // Doğru bir ifadenin sonunda yığında tam olarak bir sayı kalır
    if (stack_.size() != 1)
        throw std::runtime_error("Error");
    return stack_.top();
}

void RPN::applyOperator(char op)
{
    if (stack_.size() < 2)
        throw std::runtime_error("Error");

    // Önce sağdaki işlenen çıkar: "8 2 -" -> 8 - 2
    long right = stack_.top();
    stack_.pop();
    long left = stack_.top();
    stack_.pop();

    long result;
    if (op == '+')
        result = left + right;
    else if (op == '-')
        result = left - right;
    else if (op == '*')
        result = left * right;
    else
    {
        if (right == 0)
            throw std::runtime_error("Error");
        result = left / right;
    }

    // Değerleri int sınırında tutuyoruz; hesap long'da yapıldığı için
    // taşma olmadan önce kontrol edebiliyoruz
    if (result > INT_MAX || result < INT_MIN)
        throw std::runtime_error("Error");
    stack_.push(result);
}
