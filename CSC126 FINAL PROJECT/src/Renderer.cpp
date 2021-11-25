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
		if (customization) { customize(&customization); }

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
		ImPlot::SetNextPlotLimitsX(0, 60);
		ImPlot::SetNextPlotLimitsY(0, 500);
		if (ImPlot::BeginPlot("##FPS Graph", "Time", "FPS", {-1, 200}, ImPlotFlags_Crosshairs || ImPlotFlags_CanvasOnly))
		{
			ImPlot::PlotShaded("##FPS INLINE SHADED", &datax[0].x, &datax[0].y, datax.size(),-INFINITY, 0, 2 * sizeof(float));
			ImPlot::PlotLine("###FPS INLINE GRAPH", &datax[0].x, &datax[0].y, datax.size(), 0, 2*sizeof(float));
			ImPlot::EndPlot();
		}
		char tempo[] = "Amazing";
		if (ImGui::BeginChild("Consoles", 0, true))
		{
			ImGui::InputTextMultiline("##Logging Console", tempo,2* sizeof(tempo), { -1, 0 }, ImGuiInputTextFlags_ReadOnly || ImGuiInputTextFlags_NoMarkEdited);

		}
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
void render::table(bool* open)
{
	if (ImGui::Begin("Table", open, ImGuiWindowFlags_MenuBar))
	{
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
			ImGui::EndMenuBar();
		}
		ImGui::Dummy({0.0f, 35.0f});
		for (int h = 0; h < API.size(); h++)
		{
			if ((bool)API[h].isdefault)
			{
				ImGui::Text(API[h].name.c_str());
				if (table_horizontal)
				{
					t_horizon(h);
				}
				else if (table_vertical)
				{
					t_vertical(h);
				}
			}
		}
		ImGui::End();
	}
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

void render::initall()
{
	int a;
	a = glfwinit();
	imguiinit();
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
		ImGui::TableNextRow();
		for (int index = 0; index < API[h].data.size(); index++)
		{
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("%s", day[index].c_str());
			for (int j = 0; j < API[h].data[index].size() - 1; j++)
			{
				ImGui::TableSetColumnIndex(j + 1);
				ImGui::Text("%s", API[h].data[index][j].c_str());
			}
			ImGui::TableNextRow();
		}
		ImGui::EndTable();
	}
}

void render::t_vertical(int h)
{
	if (ImGui::BeginTable("Jadual", 8, ImGuiTableFlags_Borders))
	{
		ImGui::TableNextRow();
		ImGui::TableSetColumnIndex(0);
		ImGui::Text("Hari");
		int count = 8;
		for (int row = -1; row < API[h].time_stamp_limit; row++)
		{
			ImGui::TableSetColumnIndex(0);
			if (row % 2 == 0)
				ImGui::Text("%d:00", count);
			else if (row % 2 == 1)
				ImGui::Text("%d:30", count++);
			for (int i = 0 ; i < 7 ; i++)
			{
				ImGui::TableNextColumn();
				if (row == -1)
					ImGui::Text(day[i].c_str());
				else
					ImGui::Text("%s", API[h].data[i][row].c_str());
			}
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

void render::customize(bool* open) 
{
	if (ImGui::Begin("##Customizing", open))
	{
		ImGui::ColorPicker3("##Color Picker", &clear.x);
		ImGui::End();
	}
}

void render::fpsgraph()
{
	t += ImGui::GetIO().DeltaTime;
	spdlog::info("Time t = {}", t);
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