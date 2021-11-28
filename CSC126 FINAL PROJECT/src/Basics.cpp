#include "pch.h"
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

float CalculateCPULoad(unsigned long long idleTicks, unsigned long long totalTicks)
{
	static unsigned long long _previousTotalTicks = 0;
	static unsigned long long _previousIdleTicks = 0;

	unsigned long long totalTicksSinceLastTime = totalTicks - _previousTotalTicks;
	unsigned long long idleTicksSinceLastTime = idleTicks - _previousIdleTicks;

	float ret = 1.0f - ((totalTicksSinceLastTime > 0) ? ((float)idleTicksSinceLastTime) / totalTicksSinceLastTime : 0);

	_previousTotalTicks = totalTicks;
	_previousIdleTicks = idleTicks;
	return ret;
}

static unsigned long long FileTimeToInt64(const FILETIME& ft) { return (((unsigned long long)(ft.dwHighDateTime)) << 32) | ((unsigned long long)ft.dwLowDateTime); }

// Returns 1.0f for "CPU fully pinned", 0.0f for "CPU idle", or somewhere in between
// You'll need to call this at regular intervals, since it measures the load between
// the previous call and the current one.  Returns -1.0 on error.
float basic::GetCPULoad()
{
	FILETIME idleTime, kernelTime, userTime;
	return GetSystemTimes(&idleTime, &kernelTime, &userTime) ? CalculateCPULoad(FileTimeToInt64(idleTime), FileTimeToInt64(kernelTime) + FileTimeToInt64(userTime)) : -1.0f;
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