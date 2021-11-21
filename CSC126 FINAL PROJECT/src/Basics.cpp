#include "Basics.h"

void basic::clear()
{
	system("cls");
}

void basic::pause()
{
	CONSOLE("");
	system("pause");
}

void basic::print_color(const std::string& text, bool nextline, int mode, int color)
{
	std::cout << "\033[" + std::to_string(mode) + ";" + std::to_string(color) + "m" << text;
	std::cout << "\033[0;0m";
	nextline ? std::cout << std::endl : std::cout << "";
}

#if _DEBUG
void basic::print_1D_vector(const std::vector<std::string>& array)
{
	for (const std::string& element : array)
		CONSOLE(element);
}

void basic::print_2D_vector(const std::vector<std::vector<std::string>>& array)
{
	for (const std::vector<std::string>& row : array)
	{
		for (const std::string& element : row)
			CONSOLE1(element + ",");
		CONSOLE("");
	}
}
#endif