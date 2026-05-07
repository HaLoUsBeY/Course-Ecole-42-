#include <iostream>
#include <fstream>
#include <string>

std::string replaceAll(const std::string& content, const std::string& s1, const std::string& s2)
{
	if (s1.empty())
		return content;
	
	std::string result;
	size_t pos = 0;
	size_t lastPos = 0;
	
	while ((pos = content.find(s1, lastPos)) != std::string::npos)
	{
		result.append(content, lastPos, pos - lastPos);
		result.append(s2);
		lastPos = pos + s1.length();
	}
	result.append(content, lastPos, std::string::npos);
	
	return result;
}

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		std::cerr << "Usage: " << argv[0] << " <filename> <s1> <s2>" << std::endl;
		return 1;
	}
	
	std::string filename = argv[1];
	std::string s1 = argv[2];
	std::string s2 = argv[3];
	
	if (s1.empty())
	{
		std::cerr << "Error: s1 cannot be empty" << std::endl;
		return 1;
	}
	
	std::ifstream infile(filename.c_str());
	if (!infile.is_open())
	{
		std::cerr << "Error: Could not open file '" << filename << "'" << std::endl;
		return 1;
	}
	
	std::string content;
	std::string line;
	
	while (std::getline(infile, line))
	{
		content += line;
		if (!infile.eof())
			content += "\n";
	}
	
	if (infile.bad())
	{
		std::cerr << "Error: Failed to read file '" << filename << "'" << std::endl;
		infile.close();
		return 1;
	}
	
	infile.close();
	
	std::string result = replaceAll(content, s1, s2);
	
	std::string outfilename = filename + ".replace";
	std::ofstream outfile(outfilename.c_str());
	
	if (!outfile.is_open())
	{
		std::cerr << "Error: Could not create file '" << outfilename << "'" << std::endl;
		return 1;
	}
	
	outfile << result;
	outfile.close();
	
	std::cout << "File '" << outfilename << "' created successfully." << std::endl;
	
	return 0;
}
