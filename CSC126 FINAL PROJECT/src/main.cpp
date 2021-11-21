#include "Header.h"
#include "Basics.h"
#include "table.h"

namespace run
{
	// Main function
	int run()
	{
		table data("data/defaultTable.txt");
		int user;
	restart:
		menu();
		std::cin >> user;
		switch (user)
		{
		case 1:
			mainmenu();
			break;
		case 2:
			data.printTable();
			break;
		case 3:
			data.createTable();
			break;
		case 4:
			data.readAllTable();
			break;
		case 5:
			return 0;
		}
		basic::pause();
		goto restart;
	}

	// Another Function Section
	void menu()
	{
		const std::vector<std::string> list{
			"Main Page",
			"Default Timetable",
			"Create your own timetable",
			"View All saved timetable",
			"Exit"
		};
		basic::clear();
		basic::print_color("Welcome to Student Management CLI V2.0", true, 0, 33);
		for (int i = 0; i < list.size(); i++)
			basic::print_color(std::to_string(i + 1) + ". " + list[i], true, 0, 32);
		basic::print_color("Your input here: ", false, 0, 34);
	}

	void mainmenu()
	{
		uint8_t color = 35;
		basic::clear();
		basic::print_color("============== This Programe created by : ============== ", true, 0, 36);
		basic::print_color("1. Amirul Akmal bin Khairul Izwan", true, 0, color);
		basic::print_color("2. Izzul Hadi bin Zulkefli", true, 0, color);
		basic::print_color("3. Nafiz Izzuddin bin Mohd Saipol", true, 0, color);
	}
}

running::~running()
{
	basic::clear();
	basic::print_color("Thank you for using our Student Management CLI V2.0", true, 0, 31);
	basic::pause();
}