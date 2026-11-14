#include "PmergeMe.hpp"

#include <algorithm>
#include <cctype>
#include <climits>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string>

PmergeMe::PmergeMe()
{
}

PmergeMe::PmergeMe(const PmergeMe &other) : vec_(other.vec_), deq_(other.deq_)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vec_ = other.vec_;
        deq_ = other.deq_;
    }
    return *this;
}

PmergeMe::~PmergeMe()
{
}

// ---------------------------------------------------------------------------
// Yardımcılar
// ---------------------------------------------------------------------------

// Sadece rakamlardan oluşan ve int'e sığan sayıları kabul eder (0 dahil).
// "-1", "+5", "abc", "2147483648" -> hata
static int toNumber(const std::string &token)
{
    for (size_t i = 0; i < token.size(); i++)
    {
        if (!std::isdigit(static_cast<unsigned char>(token[i])))
            throw std::runtime_error("Error");
    }
    long number = std::strtol(token.c_str(), NULL, 10);
    if (number > INT_MAX)
        throw std::runtime_error("Error");
    return static_cast<int>(number);
}

static double elapsedMicroseconds(std::clock_t start)
{
    return static_cast<double>(std::clock() - start) * 1000000.0 / CLOCKS_PER_SEC;
}

// ---------------------------------------------------------------------------
// Program akışı
// ---------------------------------------------------------------------------

void PmergeMe::run(int argc, char **argv)
{
    // Girdiyi doğrula ve sırasız halini yaz (süreye dahil değil).
    // Hatalı girdide burada exception atılır ve hiçbir şey yazılmaz.
    fillVector(argc, argv);
    std::cout << "Before:";
    for (size_t i = 0; i < vec_.size(); i++)
        std::cout << " " << vec_[i];
    std::cout << std::endl;

    // Süre = veriyi container'a yükleme + sıralama
    std::clock_t start = std::clock();
    fillVector(argc, argv);
    sortVector();
    double vectorTime = elapsedMicroseconds(start);

    start = std::clock();
    fillDeque(argc, argv);
    sortDeque();
    double dequeTime = elapsedMicroseconds(start);

    std::cout << "After:";
    for (size_t i = 0; i < vec_.size(); i++)
        std::cout << " " << vec_[i];
    std::cout << std::endl;

    std::cout << std::fixed << std::setprecision(5);
    std::cout << "Time to process a range of " << vec_.size()
              << " elements with std::vector : " << vectorTime << " us" << std::endl;
    std::cout << "Time to process a range of " << deq_.size()
              << " elements with std::deque : " << dequeTime << " us" << std::endl;
}

// ===========================================================================
// Ford-Johnson (merge-insertion) - std::vector
//
// Değerlerin kendisini değil, vec_ içindeki konumlarını (indeks) sıralıyoruz.
// Karşılaştırma her zaman vec_[indeks] ile yapılır. Böylece aynı sayıdan
// birden çok olsa bile her küçük elemanın hangi büyükle eşli olduğu karışmaz.
// ===========================================================================

void PmergeMe::fillVector(int argc, char **argv)
{
    vec_.clear();
    for (int i = 1; i < argc; i++)
    {
        // "3 5 9" gibi tek argümanda birden çok sayı da olabilir
        std::istringstream iss(argv[i]);
        std::string token;
        while (iss >> token)
            vec_.push_back(toNumber(token));
    }
    if (vec_.empty())
        throw std::runtime_error("Error");
}

void PmergeMe::sortVector()
{
    std::vector<size_t> items;
    for (size_t i = 0; i < vec_.size(); i++)
        items.push_back(i);

    std::vector<size_t> order = mergeInsertVector(items);

    std::vector<int> sorted;
    for (size_t i = 0; i < order.size(); i++)
        sorted.push_back(vec_[order[i]]);
    vec_ = sorted;
}

std::vector<size_t> PmergeMe::mergeInsertVector(const std::vector<size_t> &items) const
{
    if (items.size() < 2)
        return items;

    // 1) İkişerli çiftler: büyük olan bigs'e girer, küçüğü onun eşi olur.
    std::vector<size_t> bigs;
    std::vector<size_t> partner(vec_.size()); // partner[büyük] = küçük
    for (size_t i = 0; i + 1 < items.size(); i += 2)
    {
        size_t first = items[i];
        size_t second = items[i + 1];
        if (vec_[first] < vec_[second])
            std::swap(first, second);
        bigs.push_back(first);
        partner[first] = second;
    }

    // 2) Büyükleri aynı algoritmayla sırala (özyineleme).
    bigs = mergeInsertVector(bigs);

    // 3) Bekleyenler: pend[k] = bigs[k]'nin eşi.
    //    Eleman sayısı tekse, çifti olmayan son eleman da en sona eklenir.
    std::vector<size_t> pend;
    for (size_t k = 0; k < bigs.size(); k++)
        pend.push_back(partner[bigs[k]]);
    if (items.size() % 2 == 1)
        pend.push_back(items[items.size() - 1]);

    // 4) Ana zincir: pend[0] + sıralı büyükler.
    //    pend[0] <= bigs[0] olduğundan başa karşılaştırmasız konur.
    std::vector<size_t> chain;
    chain.push_back(pend[0]);
    chain.insert(chain.end(), bigs.begin(), bigs.end());

    // 5) Kalanları Jacobsthal gruplarıyla ekle (numaralar 1'den başlar):
    //    3 2 | 5 4 | 11 10 9 8 7 6 | 21 ... 12 | ...
    //    Her grup kendi içinde büyük numaradan küçüğe doğru eklenir.
    size_t prevJ = 1;
    size_t currJ = 3;
    while (prevJ < pend.size())
    {
        size_t last = std::min(currJ, pend.size());

        // k azaldıkça eşi olan büyük (bigs[k-1]) zincirde hep daha solda kalır.
        // Bu yüzden onu her seferinde baştan aramak yerine, bir önceki
        // bulduğumuz yerden sola doğru aramaya devam ediyoruz (right).
        size_t right = chain.size();
        for (size_t k = last; k > prevJ; k--)
        {
            size_t item = pend[k - 1];

            // Arama sınırı: eşi olan büyüğün zincirdeki yeri (item ondan büyük olamaz).
            // Eşsiz son eleman için bütün zincir aranır.
            size_t end = chain.size();
            if (k - 1 < bigs.size())
            {
                while (chain[right - 1] != bigs[k - 1])
                    right--;
                end = right - 1;
            }

            size_t pos = binarySearchVector(chain, end, item);
            chain.insert(chain.begin() + pos, item);

            if (k - 1 >= bigs.size())
                right = chain.size(); // eşsiz eleman eklendi, zincir uzadı
        }
        size_t nextJ = currJ + 2 * prevJ; // J(n) = J(n-1) + 2 * J(n-2)
        prevJ = currJ;
        currJ = nextJ;
    }
    return chain;
}

// chain[0 .. end) aralığında item'ın girmesi gereken konumu ikili aramayla bulur
size_t PmergeMe::binarySearchVector(const std::vector<size_t> &chain, size_t end, size_t item) const
{
    size_t low = 0;
    size_t high = end;
    while (low < high)
    {
        size_t mid = low + (high - low) / 2;
        if (vec_[chain[mid]] < vec_[item])
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}

// ===========================================================================
// Ford-Johnson (merge-insertion) - std::deque
// Mantık vector sürümüyle aynı; sadece container std::deque.
// ===========================================================================

void PmergeMe::fillDeque(int argc, char **argv)
{
    deq_.clear();
    for (int i = 1; i < argc; i++)
    {
        std::istringstream iss(argv[i]);
        std::string token;
        while (iss >> token)
            deq_.push_back(toNumber(token));
    }
    if (deq_.empty())
        throw std::runtime_error("Error");
}

void PmergeMe::sortDeque()
{
    std::deque<size_t> items;
    for (size_t i = 0; i < deq_.size(); i++)
        items.push_back(i);

    std::deque<size_t> order = mergeInsertDeque(items);

    std::deque<int> sorted;
    for (size_t i = 0; i < order.size(); i++)
        sorted.push_back(deq_[order[i]]);
    deq_ = sorted;
}

std::deque<size_t> PmergeMe::mergeInsertDeque(const std::deque<size_t> &items) const
{
    if (items.size() < 2)
        return items;

    // 1) Çiftler
    std::deque<size_t> bigs;
    std::deque<size_t> partner(deq_.size());
    for (size_t i = 0; i + 1 < items.size(); i += 2)
    {
        size_t first = items[i];
        size_t second = items[i + 1];
        if (deq_[first] < deq_[second])
            std::swap(first, second);
        bigs.push_back(first);
        partner[first] = second;
    }

    // 2) Büyükleri özyinelemeli sırala
    bigs = mergeInsertDeque(bigs);

    // 3) Bekleyenler (+ varsa eşsiz son eleman)
    std::deque<size_t> pend;
    for (size_t k = 0; k < bigs.size(); k++)
        pend.push_back(partner[bigs[k]]);
    if (items.size() % 2 == 1)
        pend.push_back(items[items.size() - 1]);

    // 4) Ana zincir
    std::deque<size_t> chain;
    chain.push_back(pend[0]);
    chain.insert(chain.end(), bigs.begin(), bigs.end());

    // 5) Jacobsthal sırasıyla ekleme
    size_t prevJ = 1;
    size_t currJ = 3;
    while (prevJ < pend.size())
    {
        size_t last = std::min(currJ, pend.size());
        size_t right = chain.size();
        for (size_t k = last; k > prevJ; k--)
        {
            size_t item = pend[k - 1];

            size_t end = chain.size();
            if (k - 1 < bigs.size())
            {
                while (chain[right - 1] != bigs[k - 1])
                    right--;
                end = right - 1;
            }

            size_t pos = binarySearchDeque(chain, end, item);
            chain.insert(chain.begin() + pos, item);

            if (k - 1 >= bigs.size())
                right = chain.size();
        }
        size_t nextJ = currJ + 2 * prevJ;
        prevJ = currJ;
        currJ = nextJ;
    }
    return chain;
}

size_t PmergeMe::binarySearchDeque(const std::deque<size_t> &chain, size_t end, size_t item) const
{
    size_t low = 0;
    size_t high = end;
    while (low < high)
    {
        size_t mid = low + (high - low) / 2;
        if (deq_[chain[mid]] < deq_[item])
            low = mid + 1;
        else
            high = mid;
    }
    return low;
}
