#include <iostream>
#include <cctype>

int	main(int argc, char *argv[])
{
	if (argc == 1)
	{
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (0);
	}

	for (int arg_idx = 1; arg_idx < argc; arg_idx++)
	{
		for (int char_idx = 0; argv[arg_idx][char_idx]; char_idx++)
		{
			std::cout << (char)std::toupper(argv[arg_idx][char_idx]);//static cast 65 -> 'A;
		}
	}
	std::cout << std::endl;
	return (0);
}
