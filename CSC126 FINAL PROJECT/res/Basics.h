#pragma once

// External Lib Header
// All commeneted out include(s) will be un-comment when in needed
// #include "boost/asio/thread_pool.hpp"
// #include "boost/asio/post.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

// GUI Stuff
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "implot/epezent_implot/implot.h"
#include "implot/epezent_implot/implot_internal.h"
#include "implot/epezent_implot/implot_internal.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include <tchar.h>

// STL
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
// #include <mutex>
#include <chrono>

// Headers
#include "Definitive.h"

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