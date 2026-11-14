#include "BitcoinExchange.hpp"

#include <cctype>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>

BitcoinExchange::BitcoinExchange()
{
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) : rates_(other.rates_)
{
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
        rates_ = other.rates_;
    return *this;
}

BitcoinExchange::~BitcoinExchange()
{
}

// Windows'ta kaydedilmiş dosyalarda satır sonunda '\r' kalabilir
static void removeCarriageReturn(std::string &line)
{
    if (!line.empty() && line[line.size() - 1] == '\r')
        line.erase(line.size() - 1);
}

bool BitcoinExchange::loadDatabase(const std::string &filename)
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open database." << std::endl;
        return false;
    }

    std::string line;
    std::getline(file, line); // başlık satırı: date,exchange_rate
    while (std::getline(file, line))
    {
        removeCarriageReturn(line);
        if (line.empty())
            continue;

        size_t comma = line.find(',');
        double rate = 0;
        if (comma == std::string::npos
            || !isValidDate(line.substr(0, comma))
            || !parseNumber(line.substr(comma + 1), rate)
            || rate < 0)
        {
            std::cout << "Error: bad database line => " << line << std::endl;
            return false;
        }
        rates_[line.substr(0, comma)] = rate;
    }

    if (rates_.empty())
    {
        std::cout << "Error: empty database." << std::endl;
        return false;
    }
    return true;
}

bool BitcoinExchange::processInput(const std::string &filename) const
{
    std::ifstream file(filename.c_str());
    if (!file.is_open())
    {
        std::cout << "Error: could not open file." << std::endl;
        return false;
    }

    // 1000 * 66000 gibi sonuçlar bilimsel gösterime (6.6e+07) düşmesin diye
    std::cout << std::setprecision(10);

    std::string line;
    // İlk satır bile okunamıyorsa dosya boştur ya da bir klasördür
    if (!std::getline(file, line))
    {
        std::cout << "Error: empty or unreadable file." << std::endl;
        return false;
    }
    removeCarriageReturn(line);
    // Başlık yoksa ilk satır da normal bir veri satırıdır
    if (line != "date | value" && !line.empty())
        processLine(line);

    while (std::getline(file, line))
    {
        removeCarriageReturn(line);
        if (!line.empty())
            processLine(line);
    }
    return true;
}

void BitcoinExchange::processLine(const std::string &line) const
{
    size_t separator = line.find(" | ");
    if (separator == std::string::npos)
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }

    std::string date = line.substr(0, separator);
    double value = 0;
    if (!isValidDate(date) || !parseNumber(line.substr(separator + 3), value))
    {
        std::cout << "Error: bad input => " << line << std::endl;
        return;
    }
    if (value < 0)
    {
        std::cout << "Error: not a positive number." << std::endl;
        return;
    }
    if (value > 1000)
    {
        std::cout << "Error: too large a number." << std::endl;
        return;
    }

    // lower_bound: anahtarı >= date olan ilk eleman.
    // Tarih birebir yoksa bir önceki (daha küçük) tarihe geçeriz.
    std::map<std::string, double>::const_iterator it = rates_.lower_bound(date);
    if (it == rates_.end() || it->first != date)
    {
        if (it == rates_.begin())
        {
            std::cout << "Error: no data before => " << date << std::endl;
            return;
        }
        --it;
    }
    std::cout << date << " => " << value << " = " << value * it->second << std::endl;
}

// Biçim: YYYY-MM-DD ve takvimde gerçekten var olan bir gün
bool BitcoinExchange::isValidDate(const std::string &date) const
{
    if (date.size() != 10 || date[4] != '-' || date[7] != '-')
        return false;
    for (size_t i = 0; i < date.size(); i++)
    {
        if (i == 4 || i == 7)
            continue;
        if (!std::isdigit(static_cast<unsigned char>(date[i])))
            return false;
    }

    int year = std::atoi(date.substr(0, 4).c_str());
    int month = std::atoi(date.substr(5, 2).c_str());
    int day = std::atoi(date.substr(8, 2).c_str());
    if (month < 1 || month > 12 || day < 1)
        return false;

    int daysInMonth[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    bool isLeap = (year % 4 == 0 && year % 100 != 0) || year % 400 == 0;
    if (month == 2 && isLeap)
        return day <= 29;
    return day <= daysInMonth[month - 1];
}

// "3", "-1", "1.2" gibi düz sayıları kabul eder; "abc", "1.2.3", "1e3", "" reddedilir
bool BitcoinExchange::parseNumber(const std::string &str, double &value) const
{
    size_t i = 0;
    bool hasDigit = false;
    bool hasDot = false;

    if (i < str.size() && (str[i] == '-' || str[i] == '+'))
        i++;
    for (; i < str.size(); i++)
    {
        if (std::isdigit(static_cast<unsigned char>(str[i])))
            hasDigit = true;
        else if (str[i] == '.' && !hasDot)
            hasDot = true;
        else
            return false;
    }
    if (!hasDigit)
        return false;
    value = std::strtod(str.c_str(), NULL);
    return true;
}
