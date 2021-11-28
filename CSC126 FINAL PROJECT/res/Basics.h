#pragma once


// Easy Usage
// Mostly for debug
#define CONSOLE(x) std::cout << x << std::endl
#define CONSOLE1(x) std::cout << x

/// <summary>
/// Data Movement from JSON API to ImGui 
/// Collect all table and is_default option in the gui
/// </summary>
struct table_transfer
{
	bool isdefault = false;
	int time_stamp_limit = 0;
	std::string name{};
	std::vector<std::vector<std::string>> data;
};

struct storage_parser
{
	std::string name{};
	float x, y, z, a;
};
namespace basic
{
	/// <summary>
	/// Clear the screen totally
	/// </summary>
	void clear();

	/// <summary>
	/// To pause the program and user need to press any key to continue
	/// </summary>
	void pause();

	/// <summary>
	/// This function will print a colored text using ANSI ESC
	/// </summary>
	/// <param name="text"> - Your text</param>
	/// <param name="nextline"> - want to go next line or not</param>
	/// <param name="mode"> - 0 or 1</param>
	/// <param name="color"> - Color</param>
	/// https://ss64.com/nt/syntax-ansi.html
	void print_color(const std::string& text, bool nextline, int mode, int color);

	float GetCPULoad();
	

#if _DEBUG
	/// <summary>
	/// Debugging purposes only
	/// </summary>
	void print_1D_vector(const std::vector<std::string>& array);

	/// <summary>
	/// Debungging purposes only
	/// </summary>
	void print_2D_vector(const std::vector<std::vector<std::string>>& array);
#endif
}