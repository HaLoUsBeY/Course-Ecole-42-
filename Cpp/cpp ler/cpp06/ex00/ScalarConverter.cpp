#include "ScalarConverter.hpp"

#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstdlib>
#include <cerrno>
#include <cctype>
#include <cmath>
#include <limits>

/* ===================== OCF (private) ===================== */

ScalarConverter::ScalarConverter()
{
}

ScalarConverter::ScalarConverter(const ScalarConverter& other)
{
    (void)other;
}

ScalarConverter& ScalarConverter::operator=(const ScalarConverter& other)
{
    (void)other;
    return *this;
}

ScalarConverter::~ScalarConverter()
{
}

/*
 * Aşağıdaki yardımcılar sınıf üyesi değil, bu dosyaya özel (static)
 * fonksiyonlar: subject sınıfta yalnızca tek static metot (convert) istiyor.
 */

enum LiteralType
{
    TYPE_CHAR,
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_INVALID
};

/* ===================== Tip tespiti ===================== */

// Başta + veya - varsa 1, yoksa 0 döner (ilk rakamın indeksi)
static size_t skipSign(const std::string& s)
{
    if (!s.empty() && (s[0] == '+' || s[0] == '-'))
        return 1;
    return 0;
}

static bool isCharLiteral(const std::string& s)
{
    // 'a' biçimi
    if (s.length() == 3 && s[0] == '\'' && s[2] == '\'')
        return true;
    // Kabuk tırnakları sildiğinde gelen tek karakter (rakam olmamalı)
    return s.length() == 1 && !std::isdigit(static_cast<unsigned char>(s[0]));
}

static bool isIntLiteral(const std::string& s)
{
    size_t i = skipSign(s);

    if (i == s.length())
        return false;
    while (i < s.length())
    {
        if (!std::isdigit(static_cast<unsigned char>(s[i])))
            return false;
        i++;
    }
    return true;
}

// "42.0", "-4.2", ".5", "42." : en az bir rakam ve tam bir nokta
static bool isDecimal(const std::string& s)
{
    size_t i = skipSign(s);
    int digits = 0;
    int dots = 0;

    while (i < s.length())
    {
        if (s[i] == '.')
            dots++;
        else if (std::isdigit(static_cast<unsigned char>(s[i])))
            digits++;
        else
            return false;
        i++;
    }
    return digits > 0 && dots == 1;
}

static bool isFloatLiteral(const std::string& s)
{
    if (s == "nanf" || s == "+inff" || s == "-inff")
        return true;
    if (s.length() < 2 || s[s.length() - 1] != 'f')
        return false;
    return isDecimal(s.substr(0, s.length() - 1));
}

static bool isDoubleLiteral(const std::string& s)
{
    if (s == "nan" || s == "+inf" || s == "-inf")
        return true;
    return isDecimal(s);
}

static LiteralType detectType(const std::string& s)
{
    if (isCharLiteral(s))
        return TYPE_CHAR;
    if (isIntLiteral(s))
        return TYPE_INT;
    if (isFloatLiteral(s))
        return TYPE_FLOAT;
    if (isDoubleLiteral(s))
        return TYPE_DOUBLE;
    return TYPE_INVALID;
}

/* ===================== Aralık kontrolleri ===================== */

static bool isNan(double d)
{
    // NaN kendisine eşit olmayan tek değerdir
    return d != d;
}

static bool isInf(double d)
{
    return d == std::numeric_limits<double>::infinity()
        || d == -std::numeric_limits<double>::infinity();
}

// char için ASCII aralığı (0-127) kabul edilir
static bool fitsChar(double d)
{
    return !isNan(d) && d >= 0 && d <= 127;
}

static bool fitsInt(double d)
{
    return !isNan(d)
        && d >= static_cast<double>(std::numeric_limits<int>::min())
        && d <= static_cast<double>(std::numeric_limits<int>::max());
}

// nan ve inf float'ta da var; yalnız çok büyük sonlu değerler sığmaz
static bool fitsFloat(double d)
{
    if (isNan(d) || isInf(d))
        return true;
    return d >= -std::numeric_limits<float>::max()
        && d <= std::numeric_limits<float>::max();
}

/* ===================== Yazdırma ===================== */

// Tam sayı değerliyse "42.0" gibi; değilse en fazla 'precision' basamak
static std::string formatNumber(double d, int precision)
{
    std::ostringstream out;

    if (!isNan(d) && !isInf(d) && d == std::floor(d))
        out << std::fixed << std::setprecision(1) << d;
    else
        out << std::setprecision(precision) << d;
    return out.str();
}

static void printChar(char c)
{
    if (std::isprint(static_cast<unsigned char>(c)))
        std::cout << "char: '" << c << "'" << std::endl;
    else
        std::cout << "char: Non displayable" << std::endl;
}

static void printInt(int i)
{
    std::cout << "int: " << i << std::endl;
}

static void printFloat(float f)
{
    std::cout << "float: "
              << formatNumber(static_cast<double>(f), std::numeric_limits<float>::digits10)
              << "f" << std::endl;
}

static void printDouble(double d)
{
    std::cout << "double: "
              << formatNumber(d, std::numeric_limits<double>::digits10)
              << std::endl;
}

static void printImpossible(const std::string& typeName)
{
    std::cout << typeName << ": impossible" << std::endl;
}

static void printAllImpossible()
{
    printImpossible("char");
    printImpossible("int");
    printImpossible("float");
    printImpossible("double");
}

/* ===== Gerçek tipten diğer üç tipe açık (static_cast) dönüşüm ===== */

static void convertFromChar(char c)
{
    printChar(c);
    printInt(static_cast<int>(c));
    printFloat(static_cast<float>(c));
    printDouble(static_cast<double>(c));
}

static void convertFromInt(int i)
{
    if (fitsChar(static_cast<double>(i)))
        printChar(static_cast<char>(i));
    else
        printImpossible("char");
    printInt(i);
    printFloat(static_cast<float>(i));
    printDouble(static_cast<double>(i));
}

static void convertFromFloat(float f)
{
    // Kontrolleri double'da yap (float -> double kayıpsız)
    double asDouble = static_cast<double>(f);

    if (fitsChar(asDouble))
        printChar(static_cast<char>(f));
    else
        printImpossible("char");
    if (fitsInt(asDouble))
        printInt(static_cast<int>(f));
    else
        printImpossible("int");
    printFloat(f);
    // Değer float hassasiyetinde; double'ı da o kadar basamakla yaz (42.42f -> 42.42)
    std::cout << "double: "
              << formatNumber(asDouble, std::numeric_limits<float>::digits10)
              << std::endl;
}

static void convertFromDouble(double d)
{
    if (fitsChar(d))
        printChar(static_cast<char>(d));
    else
        printImpossible("char");
    if (fitsInt(d))
        printInt(static_cast<int>(d));
    else
        printImpossible("int");
    if (fitsFloat(d))
        printFloat(static_cast<float>(d));
    else
        printImpossible("float");
    printDouble(d);
}

/* ===================== String -> gerçek tip ===================== */

static void handleChar(const std::string& s)
{
    if (s.length() == 3)
        convertFromChar(s[1]);  // 'a'
    else
        convertFromChar(s[0]);  // a
}

// handleDouble önce tanımlı: int ve float taşınca buna düşer
static void handleDouble(const std::string& s)
{
    errno = 0;
    double value = std::strtod(s.c_str(), NULL);

    // double'a bile sığmıyor (strtod sonsuz + ERANGE döndürdü)
    if (errno == ERANGE && isInf(value))
    {
        printAllImpossible();
        return;
    }
    convertFromDouble(value);
}

static void handleFloat(const std::string& s)
{
    errno = 0;
    // C++98'de strtof yok: strtod ile okuyup float'a çeviriyoruz
    double value = std::strtod(s.c_str(), NULL);

    if (errno == ERANGE || !fitsFloat(value))
    {
        handleDouble(s);
        return;
    }
    convertFromFloat(static_cast<float>(value));
}

static void handleInt(const std::string& s)
{
    errno = 0;
    long value = std::strtol(s.c_str(), NULL, 10);

    // int'e sığmayan tam sayı (ör. 2147483648): double gibi işle
    if (errno == ERANGE
        || value < std::numeric_limits<int>::min()
        || value > std::numeric_limits<int>::max())
    {
        handleDouble(s);
        return;
    }
    convertFromInt(static_cast<int>(value));
}

/* ===================== Tek public metot ===================== */

void ScalarConverter::convert(const std::string& literal)
{
    switch (detectType(literal))
    {
        case TYPE_CHAR:
            handleChar(literal);
            break;
        case TYPE_INT:
            handleInt(literal);
            break;
        case TYPE_FLOAT:
            handleFloat(literal);
            break;
        case TYPE_DOUBLE:
            handleDouble(literal);
            break;
        default:
            printAllImpossible();
            break;
    }
}
