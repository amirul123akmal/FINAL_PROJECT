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
	void loadTableToFile();

public:
	table(const char path[]);

	void printTable();

	void createTable();

	void readAllTable();
	
	~table();
};

class json_table
{
public:
	json_table();
	~json_table();
	void loadtable(std::string a);
	void update();

private:
	nlohmann::json j;
	std::vector<std::string> json_data{};
	std::vector<std::string> available_table{};
protected:
	int time_stamp_limit = 0;
	const std::vector<std::string> day{
	"Isnin", "Selasa", "Rabu", "Khamis", "Jumaat", "Sabtu", "Ahad"
	};
	std::vector<std::vector<std::string>> table_data{};
};