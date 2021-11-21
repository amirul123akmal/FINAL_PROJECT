#include "Basics.h"

class table
{
private:
	// Table
	std::ifstream defaultTable;
	std::vector<std::vector<std::string>> tableData{}, createTableData{};
	std::vector<std::string> row{}, createRow{}, day{"Isnin","Selasa", "Rabu", "Khamis", "Jumaat", "Sabtu","Ahad"};

	// Windows / Console stuff
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos{};

	// Table Creation stuff
	std::string tableName{}, temp{};

private:
	void loadTableToMemory();

public:
	table(const char path[]);

	void printTable();

	void createTable();
	
	~table();
};