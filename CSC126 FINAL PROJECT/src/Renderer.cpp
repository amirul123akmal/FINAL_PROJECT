#include "pch.h"
#include "Renderer.h"

// The main loop
int render::runMainProcess()
{
	lasttime = glfwGetTime();
	while (!glfwWindowShouldClose(window) && !exit)
	{
		// Set New Frame
		glfwPollEvents();
		new_frame();

		// Frame body
		menubar();
		fpsgraph();
		if (debug) debug_mode(&debug);
		if (home) homepage(&home);
		if (createtable) { tablecreation(&createtable); }
		if (opentable) { table(&opentable); }
		if (customization) { customize(&customization, clear, "Main Window"); }

		FPS_limit(FPS_LIMIT);
		// Render Frame
		ImGui::Render();
		glfwGetFramebufferSize(window, &width, &height);
		glViewport(0, 0, width, height); // dynamix sizing
		glClearColor(clear.x * clear.w, clear.y * clear.w, clear.z * clear.w, clear.w);
		glClear(GL_COLOR_BUFFER_BIT);
		::imggl_render(ImGui::GetDrawData());
		glfwSwapBuffers(window);
	}
	return 0;
}

void render::FPS_limit(int fps)
{
	while (glfwGetTime() < lasttime + 1.0 / fps) {
	}
	lasttime += 1.0 / fps;
}

void render::debug_mode(bool* open)
{
	if (ImGui::Begin("Debugging tool", open))
	{
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		ImGui::SliderInt("FPS", &FPS_LIMIT, 15, 500, "%d");
		ImGui::SameLine();
		if (ImGui::Button("Reset FPS to Default"))
			FPS_LIMIT = 60;
		ImGui::InputInt("##Set FPS", &FPS_LIMIT, 5, 50, ImGuiInputTextFlags_EnterReturnsTrue);
		ImGui::SameLine();
		ImGui::Text(" <-- Set Specific FPS");
		ImPlot::SetNextPlotLimitsX(0, 60);
		ImPlot::SetNextPlotLimitsY(0, 500);
		if (ImPlot::BeginPlot("##FPS Graph", "Time", "FPS", {-1, 200}, ImPlotFlags_Crosshairs || ImPlotFlags_CanvasOnly))
		{
			ImPlot::PlotShaded("##FPS INLINE SHADED", &datax[0].x, &datax[0].y, datax.size(),-INFINITY, 0, 2 * sizeof(float));
			ImPlot::PlotLine("###FPS INLINE GRAPH", &datax[0].x, &datax[0].y, datax.size(), 0, 2*sizeof(float));
			ImPlot::EndPlot();
		}
		char tempo[] = "Amazing";
		ImGui::InputTextMultiline("##Logging Console", tempo,2* sizeof(tempo), { -1, 0 }, ImGuiInputTextFlags_ReadOnly || ImGuiInputTextFlags_NoMarkEdited);
	}
}

void render::homepage(bool* open)
{
	if (ImGui::Begin("Homepage", open))
	{
		if (ImGui::Button("Table"))
		{
			if (opentable)
				opentable = false;
			else
				opentable = true;
		}
		if (ImGui::Button("Create Table"))
		{
			if (createtable)
				createtable = false;
			else
				createtable = true;
		}
		if (ImGui::Button("Exit"))
			exit = true;
	}
}

// Menubar
static bool table_vertical = false;
static bool table_horizontal = true;
static bool table_compressed = false;

void render::menubar()
{
	if (ImGui::BeginMainMenuBar())
	{
		ImGui::MenuItem("Homepage", 0, &home);
		if(ImGui::BeginMenu("Table"))
		{
			ImGui::MenuItem("Open Table", 0, &opentable);
			ImGui::MenuItem("Generate Custom Table", 0, &createtable);
			TableModeBar();
			ImGui::EndMenu();
		}
		ImGui::MenuItem("Customize", 0, &customization);
		ImGui::MenuItem("Debug", 0, &debug);
		ImGui::MenuItem("Exit", 0, &exit);
		ImGui::EndMainMenuBar();
	}
}

// Table
static float childHeight = 50;
static bool tablewindowbg = false;
static bool tablebg = false;
static bool tableline = false;
void render::table(bool* open)
{
	ImGui::PushStyleColor(ImGuiCol_WindowBg, TableWindowColorSpace);
	if (ImGui::Begin("Table", open, ImGuiWindowFlags_MenuBar))
	{
		ImGui::PushStyleColor(ImGuiCol_ChildBg, { 120 });
		// Area for dragging and changing the size
		if (ImGui::BeginChildFrame(tableopenarea, { -1, childHeight }, ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_AlwaysAutoResize))
		{
			if (ImGui::BeginChild(dragresizableArea, { -1, childHeight }, false))
			{
				// Capture mouse position into child area
				if (
					(ImGui::GetMousePos().x > ImGui::GetWindowPos().x && ImGui::GetMousePos().x < ImGui::GetWindowPos().x + ImGui::GetWindowWidth())
					&&
					(ImGui::GetMousePos().y > ImGui::GetWindowPos().y && ImGui::GetMousePos().y < ImGui::GetWindowPos().y + childHeight)
					)
				{
					// Vertical Spacing on Horizontal Table
					{
						if (table_horizontal)
						{
							if (spacingVertical < 0)
								spacingVertical = 0;
							spacingVertical -= ImGui::GetIO().MouseWheel;
						}
						if (table_vertical)
						{
							if (spacingVertical < 0)
								spacingVertical = 0;
							spacingVertical += ImGui::GetIO().MouseWheel;
						}
					}
					// Horizontal Spacing on Vertical Table
					{
						if (ImGui::GetIO().MouseDown[0])
						{
							spacingHorizontal += ImGui::GetIO().MouseDelta.x;
							if (spacingHorizontal > -1)
								spacingHorizontal = -1;
						}
					}
				}
			}
			ImGui::EndChild();
			ImGui::EndChildFrame();
		}
		ImGui::PopStyleColor();

		if(ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Table"))
			{
				if (ImGui::BeginMenu("List Table: "))
				{
					for (int i = 0; i < available_table.size(); i++)
						ImGui::MenuItem(API[i].name.c_str(), NULL, &API[i].isdefault);
					ImGui::EndMenu();
				}
				TableModeBar();
				ImGui::EndMenu();
			}
			if (ImGui::BeginMenu("Customize"))
			{
				ImGui::MenuItem("Table's Window Background", 0, &tablewindowbg);
				ImGui::MenuItem("Table Background", 0, &tablebg);
				ImGui::MenuItem("Table's Line", 0, &tableline);
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		if(tablewindowbg) customize(&tablewindowbg, TableWindowColorSpace, "Table Window Background");
		if(tablebg) customize(&tablebg, TableBgColorSpace, "Table Background");
		if(tableline) customize(&tableline, TableLineColorSpace, "Table line Color");

		ImGui::Separator();
		for (int h = 0; h < API.size(); h++)
		{
			if ((bool)API[h].isdefault)
			{
				ImGui::PushStyleColor(ImGuiCol_TableRowBg, TableBgColorSpace);
				ImGui::Text(API[h].name.c_str());
				if (table_horizontal)
					t_horizon(h);
				else if (table_vertical)
					t_vertical(h);
				ImGui::PopStyleColor();
			}
		}
		ImGui::End();
	}
	ImGui::PopStyleColor();
}

void render::tablecreation(bool* open)
{
	if (ImGui::Begin("Create Custom Table", open, ImGuiWindowFlags_MenuBar))
	{
		if (ImGui::BeginMenuBar())
		{
			if (ImGui::BeginMenu("Table"))
			{
				TableModeBar();
				ImGui::EndMenu();
			}
			ImGui::EndMenuBar();
		}
		ImGui::Dummy({0.0f, 35.0f});
		ImGui::Text("Name for the table: ");
		if (ImGui::InputText(namenow, name, 20, ImGuiInputTextFlags_EnterReturnsTrue))
		{
			strcpy_s(namenow, name);
			std::cout << namenow << "\n";
		}
		ImGui::Spacing();
		if (ImGui::BeginTable("Jadual", RENDER_TABLE_DEFAULT_COLUMN, ImGuiTableFlags_Borders))
		{
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Hari");
			int count = 8;
			for (int column = 1; column < RENDER_TABLE_DEFAULT_COLUMN; column++)
			{
				ImGui::TableSetColumnIndex(column);
				ImGui::Text("%d:00", count);
				ImGui::TableSetColumnIndex(++column);
				ImGui::Text("%d:30", count++);
			}
			ImGui::TableNextRow();
			for (int index = 0; index < 7; index++)
			{
				ImGui::TableSetColumnIndex(0);
				ImGui::Text("%s", day[index].c_str());
				for (int j = 0; j < RENDER_TABLE_DEFAULT_COLUMN - 1; j++)
				{
					ImGui::TableSetColumnIndex(j + 1);
				}
				ImGui::TableNextRow();
			}
			ImGui::EndTable();
		}
		ImGui::End();
	}
}

// Class upon creation & deletion setup
render::render()
{
	// setup
	glfwSetErrorCallback(glfw_error_callback);
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
}


void render::imguiinit()
{
	ImGui::CreateContext();
	ImPlot::CreateContext();
	io = ImGui::GetIO(); (void)io;
	ImGui::StyleColorsDark();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);
}

render::~render()
{
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
}

void render::glfw_error_callback(int error, const char* description)
{
	std::fprintf(stderr, "GLFW Error %d: %s", error, description);
}

void render::t_horizon(int h)
{
	if (ImGui::BeginTable("Jadual", API[h].time_stamp_limit, ImGuiTableFlags_Borders))
	{
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("Hari");
		int count = 8;
		for (int column = 1; column < API[h].time_stamp_limit; column++)
		{
			ImGui::TableSetColumnIndex(column);
			ImGui::Text("%d:00", count);
			ImGui::TableSetColumnIndex(++column);
			ImGui::Text("%d:30", count++);
		}
		for (int index = 0; index < API[h].data.size(); index++)
		{
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Dummy({0, spacingVertical});
			ImGui::Text("%s", day[index].c_str());
			ImGui::Dummy({0, spacingVertical});
			for (int j = 0; j < API[h].data[index].size() - 1; j++)
			{
				ImGui::TableSetColumnIndex(j + 1);
				ImGui::Dummy({0, spacingVertical});
				ImGui::Text("%s", API[h].data[index][j].c_str());
				ImGui::Dummy({0, spacingVertical});
			}
		}
		ImGui::EndTable();
	}
}

void render::t_vertical(int h)
{
	if (ImGui::BeginTable("Jadual", 8, ImGuiTableFlags_Borders, {spacingHorizontal, 500}))
	{
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Dummy({spacingVertical, 0});
		ImGui::SameLine();
		ImGui::Text("Hari");
		int count = 8;
		for (int row = -1; row < API[h].time_stamp_limit; row++)
		{
			ImGui::TableSetColumnIndex(0);
			ImGui::Dummy({spacingVertical, 0});
			ImGui::SameLine();
			if (row % 2 == 0)
				ImGui::Text("%d:00", count);
			else if (row % 2 == 1)
				ImGui::Text("%d:30", count++);
			for (int i = 0 ; i < 7 ; i++)
			{
				ImGui::TableNextColumn();
				ImGui::Dummy({spacingVertical, 0});
				ImGui::SameLine();
				if (row == -1)
					ImGui::Text(day[i].c_str());
				else
					ImGui::Text("%s", API[h].data[i][row].c_str());
				ImGui::Dummy({spacingVertical, 0});
			}
			if(row != API[h].time_stamp_limit - 1)
				ImGui::TableNextRow();
		}
		ImGui::EndTable();
	}
}

void render::TableModeBar()
{
	if (ImGui::BeginMenu("Table Mode"))
	{
		if (ImGui::MenuItem("Horizontal", 0, &table_horizontal))
			table_vertical = (table_horizontal) ? false :  true;
		if (ImGui::MenuItem("Vertical", 0, &table_vertical))
			table_horizontal = ( table_vertical) ? false : true;
		ImGui::MenuItem("Compress", 0, &table_compressed);
		ImGui::EndMenu();
	}
}

void render::customize(bool* open, ImVec4& data, const char* whichWindow) 
{
	if (ImGui::Begin("##Customizing", open))
	{
		ImGui::Text("%s", whichWindow);
		ImGui::ColorPicker3("##Color Picker", &data.x);
		ImGui::End();
	}
	ImGui::Dummy({0, 20});
}

void render::fpsgraph()
{
	t += ImGui::GetIO().DeltaTime;
	if (t > 60)
	{
		t = 0;
		datax.clear();
		offset = 0;
		enable = true;
	}
	datax.push_back({t, ImGui::GetIO().Framerate});
	offset = (offset + 1) % (datax.size() * 60);
}

void render::initall()
{
	int a;
	a = glfwinit();
	imguiinit();
	colorinitialization();
}

int render::glfwinit()
{
	window = glfwCreateWindow(1920, 1080, "CSC126 Mini Project", NULL, NULL);
	glfwMaximizeWindow(window);
	if (!window)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(0);
	return 0;
}

void render::colorinitialization()
{
	for (int x = 0; x < LoadedBigStorage.size(); x++)
	{
		if (LoadedBigStorage[x].name == "MainWindow")
		{
			clear.x = LoadedBigStorage[x].x;
			clear.y = LoadedBigStorage[x].y;
			clear.z = LoadedBigStorage[x].z;
			clear.w = LoadedBigStorage[x].a;
		}
	}
}