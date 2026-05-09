#include <iostream>
#include <fstream>
#include <string>

void writeReplacedLine(const std::string& line, const std::string& s1, const std::string& s2, std::ofstream& out)
{
    if (s1.empty())
	{
        out << line;
        return;
    }

    size_t start = 0;
    size_t pos;

    while ((pos = line.find(s1, start)) != std::string::npos)//No Position : npos = -1
	{
        out << line.substr(start, pos - start);
        out << s2;
        start = pos + s1.length();
    }
    out << line.substr(start);
}

int main(int argc, char **argv)
{
    if (argc != 4)
	{
        std::cerr << "Error: Missing or extra parameter!" << std::endl;
        std::cerr << "Usage: ./sed_is_for_losers <dosya_adi> <s1> <s2>" << std::endl;
        return 1;
    }

    std::string filename = argv[1];
    std::string s1 = argv[2];
    std::string s2 = argv[3];

    std::ifstream inFile(filename.c_str());//(C++98 -> .c_str())
    if (!inFile.is_open())
	{
        std::cerr << "Error: '" << filename << "' The file could not be opened or was not found!" << std::endl;
        return 1;
    }

    std::string outFilename = filename + ".replace";//abc.txt + .replace
    std::ofstream outFile(outFilename.c_str());
    if (!outFile.is_open())
	{
        std::cerr << "Error: Unable to create a new file!" << std::endl;
        inFile.close();
        return 1;
    }

    std::string line;
    while (std::getline(inFile, line))//No ram yes ram 
	{
        writeReplacedLine(line, s1, s2, outFile);
        
        if (!inFile.eof())
            outFile << std::endl;//\n
    }

    inFile.close();
    outFile.close();

    std::cout << "Success! Modified text '" << outFilename << "' was saved to the file." << std::endl;

    return 0;
}
