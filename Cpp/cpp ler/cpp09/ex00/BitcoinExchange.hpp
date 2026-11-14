#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <map>
#include <string>

class BitcoinExchange
{
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &other);
    BitcoinExchange &operator=(const BitcoinExchange &other);
    ~BitcoinExchange();

    bool loadDatabase(const std::string &filename);
    bool processInput(const std::string &filename) const;

private:
    // tarih ("YYYY-MM-DD") -> o günün bitcoin fiyatı
    std::map<std::string, double> rates_;

    bool isValidDate(const std::string &date) const;
    bool parseNumber(const std::string &str, double &value) const;
    void processLine(const std::string &line) const;
};

#endif
