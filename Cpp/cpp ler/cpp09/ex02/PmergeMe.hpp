#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <cstddef>
#include <deque>
#include <vector>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &other);
    PmergeMe &operator=(const PmergeMe &other);
    ~PmergeMe();

    void run(int argc, char **argv);

private:
    std::vector<int> vec_;
    std::deque<int> deq_;

    // std::vector sürümü
    void fillVector(int argc, char **argv);
    void sortVector();
    std::vector<size_t> mergeInsertVector(const std::vector<size_t> &items) const;
    size_t binarySearchVector(const std::vector<size_t> &chain, size_t end, size_t item) const;

    // std::deque sürümü
    void fillDeque(int argc, char **argv);
    void sortDeque();
    std::deque<size_t> mergeInsertDeque(const std::deque<size_t> &items) const;
    size_t binarySearchDeque(const std::deque<size_t> &chain, size_t end, size_t item) const;
};

#endif
