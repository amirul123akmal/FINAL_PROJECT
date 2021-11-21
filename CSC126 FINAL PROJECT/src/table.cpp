#include "table.h"

// ========== PRIVATE ==========

void table::loadTableToMemory()
{
	tableData.clear();
	std::string data;
	while (!defaultTable.eof())
	{
		row.clear();
		std::getline(defaultTable, data);
		row.push_back(data);
		std::getline(defaultTable, data);
		int num = std::stoi(data);
		for (int i = 0; i < num; i++)
		{
			std::getline(defaultTable, data);
			std::stringstream ss(data);
			while (std::getline(ss, data, ';'))
				row.push_back(data);
		}
		tableData.push_back(row);
	}
	#ifdef _DEBUG
		basic::print_2D_vector(tableData);
		basic::pause();
	#endif // _DEBUG
}

// ========== PUBLIC ==========

// Constructor
table::table(const char path[])
{
	defaultTable.open(path, std::ios::in);
	loadTableToMemory();
}

void table::printTable()
{
	basic::clear();
	int maxBorder = 0;
	bool toggle = false;
	// Get Max length for border
	for (int i = 0; i < tableData.size(); i++)
		for (int j = 0; j < tableData[i].size() - 2; j++)
			if (21 + tableData[i][static_cast<uint64_t>(j) + 1].length() > maxBorder)
				maxBorder = 15 + tableData[i][ static_cast<uint64_t>(j) + 1].length();
	for (int i = 0; i < maxBorder; i++)
		CONSOLE1("=");
	for (int i = 0; i < tableData.size(); i++)
	{
		CONSOLE1("\n|");
		basic::print_color(tableData[i][0], false, 0, 32);
		CONSOLE("|");
		for (int j = 1; j < tableData[i].size(); j++)
		{
			if (toggle)
			{
				CONSOLE1("|");
				basic::print_color(tableData[i][j], false, 0, 33);
				toggle = false;
			}
			else
			{
				CONSOLE1("|");
				basic::print_color(tableData[i][j], false, 0, 36);
				toggle = true;
			}
			GetConsoleScreenBufferInfo(h, &csbi);
			pos.X = 21;
			pos.Y = csbi.dwCursorPosition.Y;
			SetConsoleCursorPosition(h, pos);
			if (j % 2 == 0)
			{
				GetConsoleScreenBufferInfo(h, &csbi);
				pos.X = maxBorder-1;
				pos.Y = csbi.dwCursorPosition.Y;
				SetConsoleCursorPosition(h, pos);
				CONSOLE("|");
			}
		}
	}
	for (int i = 0; i < maxBorder; i++)
		CONSOLE1("=");
}

void table::createTable()
{
	int count;

	basic::clear();
	basic::print_color("Time Format", true, 0, 32);
	basic::print_color("00:00 aa - 00:00 aa", true, 0, 35);
	basic::print_color("Replace 00:00 with your time", true, 0, 34);
	basic::print_color("Replace aa with either am or pm\n", true, 0, 34);
	basic::print_color("Insert aaa123 to go to next day\n", true, 0, 34);
	basic::print_color("Insert abc123 at time to stop the table creation\n", true, 0, 34);

	basic::print_color("Enter the name of the table: ", false, 0, 31);
	std::getline(std::cin, tableName);

	for (int i = 0; i < day.size(); i++)
	{
		count = 1;
		basic::print_color("\n" + day[i], true, 0, 32);
		for (;;count++)
		{
			createRow.clear();
			basic::print_color("Enter Time: ", false, 0, 33);
			std::getline(std::cin, temp);
			if (temp == "aaa123" || temp == "abc123")
				break;
			createRow.push_back(day[i]);
			createRow.push_back(temp);
			basic::print_color("Enter Subject Code: ", false, 0, 33);
			std::getline(std::cin, temp);
			createRow.push_back(temp);
			createTableData.push_back(createRow);
		}
		if (temp == "abc123")
			break;
	}


}

 // Deconstructor
table::~table()
{
	// Just to be ready if want to put anything
}