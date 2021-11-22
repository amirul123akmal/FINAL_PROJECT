#include "Header.h"
#include "Basics.h"
#include "Renderer.h"

namespace run
{
	// Main function
	int run()
	{
		render desktop;
		desktop.initall();
		desktop.runMainProcess();
		return 0;
	}
}

running::~running()
{
}