#ifndef RPN_HPP
#define RPN_HPP

#include <list>
#include <stack>
#include <string>

class RPN
{
public:
    RPN();
    RPN(const RPN &other);
    RPN &operator=(const RPN &other);
    ~RPN();

    long evaluate(const std::string &expression);

private:
    // std::stack varsayılan olarak altta std::deque kullanır.
    // deque ex02'de lazım olduğu için burada altta std::list kullanıyoruz.
    std::stack<long, std::list<long> > stack_;

    void applyOperator(char op);
};

#endif
