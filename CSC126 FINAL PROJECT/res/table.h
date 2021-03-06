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
	void loadtable();
	void availtable();
private:
	nlohmann::json j;
	nlohmann::json BigStorage;
	std::vector<std::string> json_data{};
	std::string temp;
	int count = 1;

	void FromBigStorage();
protected:
	/// <summary>
	/// Days in a week
	/// </summary>
	const std::vector<std::string> day{
	"Isnin", "Selasa", "Rabu", "Khamis", "Jumaat", "Sabtu", "Ahad"
	};
	/// <summary>
	/// available_table index is the same as the API
	/// </summary>
	std::vector<std::string> available_table{};
	std::vector<table_transfer> API{};
	
	void colorLoadIntoDisk();
	void BigStorageUpdation(ImVec4& data, const char*);

	std::vector<storage_parser> LoadedBigStorage{};
};