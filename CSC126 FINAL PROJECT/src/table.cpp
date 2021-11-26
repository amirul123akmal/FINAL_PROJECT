#include "pch.h"
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

void table::loadTableToFile()
{
	std::ofstream file("data/"+tableName + ".txt", std::ios::out);
	for (const std::vector<std::string>& element : createTableData)
	{
		file << element[0] << "\n" << element[1] << "\n";
		for (int i = 2 ; i < element.size()-1 ; i = i + 2)
			file << element[i] << ";" << element[i+1] << "\n";
	}
	file.close();
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
	uint64_t maxBorder = 0;
	bool toggle = false;
	// Get Max length for border
	for (int i = 0; i < tableData.size(); i++)
		for (int j = 0; j < tableData[i].size() - 2; j++)
			if (21 + tableData[i][j + 1].length() > maxBorder)
				maxBorder = 15 + tableData[i][j + 1].length();
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
				pos.X = static_cast<int>(maxBorder)-1;
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
	std::cin.ignore();
	std::getline(std::cin, tableName);

	for (int i = 0; i < day.size(); i++)
	{
		createRow.clear();
		count = 0;
		basic::print_color("\n" + day[i], true, 0, 32);
		createRow.push_back(day[i]);
		createRow.push_back(std::to_string(count));
		for (;;count++)
		{
			basic::print_color("Enter Time: ", false, 0, 33);
			std::getline(std::cin, temp);
			if (temp == "aaa123" || temp == "abc123")
			{
				createRow[1] = std::to_string(count);
				createTableData.push_back(createRow);
				break;
			}
			createRow.push_back(temp);
			basic::print_color("Enter Subject Code: ", false, 0, 33);
			std::getline(std::cin, temp);
			createRow.push_back(temp);
		}
		if (temp == "abc123")
			break;
	}
	loadTableToFile();
#if _DEBUG
	basic::print_2D_vector(createTableData);
#endif

}

void table::readAllTable()
{
	for (const std::filesystem::directory_entry& i : std::filesystem::directory_iterator("data/"))
	{
		temp = i.path().string();
		temp.erase(temp.end() - 4, temp.end());
		temp.erase(temp.begin(), temp.begin()+5);
		std::cout << temp << "\n";
	}
}

 // Deconstructor
table::~table()
{
	// Just to be ready if want to put anything
}


// JSON PARSER
void json_table::loadtable()
{
	for (int k = 0; k < available_table.size(); k++)
	{
		table_transfer collect;
		json_data.clear();
		j.clear();
		// read JSON
		std::ifstream table("data/Table/"+ available_table[k] + ".json", std::ios::in);
		j = nlohmann::json::parse(table);

		collect.name = j["name"];

		if (j["open"] == "true")
			collect.isdefault = true;
		
		for (int i = 0; i < 7; i++)
		{
			json_data.clear();
			nlohmann::json js(j[day[i].c_str()]);

			if(js.size() > collect.time_stamp_limit)
				collect.time_stamp_limit = js.size();

			for (int j = 1; j <= collect.time_stamp_limit; j++)
				json_data.push_back(js[std::to_string(j).c_str()]);
			collect.data.push_back(json_data);
		}
		API.push_back(collect);
		table.close();
	}
}

void json_table::availtable()
{
	try
	{
		for (const std::filesystem::directory_entry& i : std::filesystem::directory_iterator("data/Table/"))
		{
			temp = i.path().string();
			temp.erase(temp.end() - 5, temp.end()); // remove extension
			temp.erase(temp.begin(), temp.begin() + 11); // remove parent dir
			available_table.push_back(temp);
		}
		spdlog::info("Loaded all table");
	}
	catch (std::string e)
	{
		spdlog::error("Failed load table");
	}
}

void json_table::FromBigStorage()
{
	std::ifstream storageAccess("data/Customization/Color.json", std::ios::in);
	storageAccess >> BigStorage;
	count = 1;
	std::string context;
	while (1)
	{
		storage_parser data;
		context = "data" + std::to_string(count++);
		if (!BigStorage[context.c_str()].is_null())
		{
			nlohmann::json in1(BigStorage[context.c_str()]);
			data.name = in1["name"];
			nlohmann::json in2(in1["color"]);
			data.x = in2["x"];
			data.y = in2["y"];
			data.z = in2["z"];
			data.a = in2["a"];
			LoadedBigStorage.push_back(data);
		}
		else
			break;
	}
	storageAccess.close();
}
void json_table::BigStorageUpdation(ImVec4& data, const char* name)
{
	for (int i = 0; i < LoadedBigStorage.size(); i++)
	{
		if (LoadedBigStorage[i].name == name)
		{
			LoadedBigStorage[i].x = data.x;
			LoadedBigStorage[i].y = data.y;
			LoadedBigStorage[i].z = data.z;
			LoadedBigStorage[i].a = data.w;
		}
	}
}
void json_table::colorLoadIntoDisk()
{
	std::ofstream fileHandler("data/Customization/ColorTemp.json", std::ios::out);
	count = 1;
	std::string datahandler;
	nlohmann::json superhandler;
	for (int i = 0; i < LoadedBigStorage.size(); i++)
	{
		datahandler = "data" + std::to_string(count++);
		nlohmann::json inColor;
		inColor["x"] = LoadedBigStorage[i].x;
		inColor["y"] = LoadedBigStorage[i].y;
		inColor["z"] = LoadedBigStorage[i].z;
		inColor["a"] = LoadedBigStorage[i].a;
		nlohmann::json data;
		data["name"] = LoadedBigStorage[i].name;
		data["color"] = inColor;
		superhandler[datahandler.c_str()] = data;
	}
	fileHandler << superhandler;
	fileHandler.close();
	system("del data\\Customization\\Color.json");
	system("rename data\\Customization\\ColorTemp.json Color.json");
}

json_table::json_table()
{
	availtable();
	loadtable();
	FromBigStorage();
}

json_table::~json_table()
{
}