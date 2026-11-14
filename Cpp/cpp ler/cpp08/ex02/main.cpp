#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <algorithm>
#include "MutantStack.hpp"

// Subject'teki main, MutantStack ile
static void subjectTestMutantStack()
{
    MutantStack<int> mstack;

    mstack.push(5);
    mstack.push(17);

    std::cout << mstack.top() << std::endl;

    mstack.pop();

    std::cout << mstack.size() << std::endl;

    mstack.push(3);
    mstack.push(5);
    mstack.push(737);
    //[...]
    mstack.push(0);

    MutantStack<int>::iterator it = mstack.begin();
    MutantStack<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::stack<int> s(mstack);
}

// Aynı main, std::list ile (push -> push_back, top -> back, pop -> pop_back)
static void subjectTestList()
{
    std::list<int> mstack;

    mstack.push_back(5);
    mstack.push_back(17);

    std::cout << mstack.back() << std::endl;

    mstack.pop_back();

    std::cout << mstack.size() << std::endl;

    mstack.push_back(3);
    mstack.push_back(5);
    mstack.push_back(737);
    //[...]
    mstack.push_back(0);

    std::list<int>::iterator it = mstack.begin();
    std::list<int>::iterator ite = mstack.end();

    ++it;
    --it;
    while (it != ite)
    {
        std::cout << *it << std::endl;
        ++it;
    }
    std::list<int> s(mstack);
}

// Alttan üste doğru yazdırır (const_iterator kullanır)
template <typename Stack>
void printStack(std::string const &name, Stack const &st)
{
    std::cout << name << " (size " << st.size() << "):";
    for (typename Stack::const_iterator it = st.begin(); it != st.end(); ++it)
        std::cout << " " << *it;
    std::cout << std::endl;
}

int main()
{
    std::cout << "=== subject main with MutantStack ===" << std::endl;
    subjectTestMutantStack();

    std::cout << std::endl << "=== subject main with std::list ===" << std::endl;
    subjectTestList();

    MutantStack<int> ms;
    for (int i = 1; i <= 5; i++)
        ms.push(i * 10);

    std::cout << std::endl << "=== const_iterator (bottom -> top) ===" << std::endl;
    printStack("ms", ms);

    std::cout << std::endl << "=== reverse_iterator (top -> bottom) ===" << std::endl;
    for (MutantStack<int>::reverse_iterator rit = ms.rbegin(); rit != ms.rend(); ++rit)
        std::cout << *rit << " ";
    std::cout << std::endl;
    std::cout << "top(): " << ms.top() << ", *rbegin(): " << *ms.rbegin() << std::endl;

    std::cout << std::endl << "=== modify through iterator + algorithms ===" << std::endl;
    for (MutantStack<int>::iterator it = ms.begin(); it != ms.end(); ++it)
        *it += 1;
    printStack("ms", ms);
    std::cout << "std::find(31): "
              << (std::find(ms.begin(), ms.end(), 31) != ms.end() ? "found" : "not found")
              << std::endl;
    std::cout << "std::count(21): " << std::count(ms.begin(), ms.end(), 21) << std::endl;
    std::cout << "top(): " << ms.top() << std::endl;

    std::cout << std::endl << "=== copy constructor / assignment (deep copy) ===" << std::endl;
    MutantStack<int> copy(ms);
    MutantStack<int> assigned;
    assigned = ms;
    copy.push(999);
    assigned.pop();
    printStack("ms      ", ms);
    printStack("copy    ", copy);
    printStack("assigned", assigned);

    std::cout << std::endl << "=== still a stack: pop until empty ===" << std::endl;
    while (!copy.empty())
    {
        std::cout << copy.top() << " ";
        copy.pop();
    }
    std::cout << std::endl;
    std::cout << "empty: " << (copy.empty() ? "yes" : "no")
              << ", begin() == end(): " << (copy.begin() == copy.end() ? "yes" : "no") << std::endl;

    std::cout << std::endl << "=== other types / underlying containers ===" << std::endl;
    MutantStack<std::string> words;
    words.push("bottom");
    words.push("middle");
    words.push("top");
    printStack("MutantStack<std::string>", words);

    MutantStack<int, std::vector<int> > vstack;
    vstack.push(1);
    vstack.push(2);
    vstack.push(3);
    printStack("MutantStack<int, std::vector<int> >", vstack);

    MutantStack<int, std::list<int> > lstack;
    lstack.push(4);
    lstack.push(5);
    printStack("MutantStack<int, std::list<int> >", lstack);

    return 0;
}
