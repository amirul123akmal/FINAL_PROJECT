#include "Renderer.h"

// The main loop
int render::runMainProcess()
{
	while (!glfwWindowShouldClose(window) && !exit)
	{
		// Set New Frame
		glfwPollEvents();
		new_frame();
		
		// Frame body
		homepage();
		if (createtable) { tablecreation(&createtable); }
		if (opentable) { table(&opentable); }

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

// Table
void render::homepage()
{
	if (ImGui::Begin("Homepage"))
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
		ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	}
}

void render::table(bool* open)
{
	if (ImGui::Begin("Table", open))
	{
		if (ImGui::CollapsingHeader("Table List"))
		{
			if (ImGui::BeginTable("Table", 3))
			{
				for (int i = 0; i < available_table.size(); i++)
				{
					ImGui::TableNextColumn();
					ImGui::Checkbox(API[i].name.c_str(), &API[i].isdefault);
				}
			}
			ImGui::EndTable();
		}
		for (int h = 0; h < API.size(); h++)
		{
			if ((bool)API[h].isdefault)
			{
				ImGui::Text(API[h].name.c_str());
				if (ImGui::BeginTable("Jadual", API[h].time_stamp_limit, ImGuiTableFlags_Borders))
				{
					ImGui::TableNextRow();
					ImGui::TableSetColumnIndex(0);
					ImGui::Text("Hari");
					int count = 8;
					for (int column = 1; column < API[h].time_stamp_limit ; column++)
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
		}
		ImGui::End();
	}
}

void render::tablecreation(bool* open)
{
	if (ImGui::Begin("Create Custom Table", open))
	{
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
	window = glfwCreateWindow(1280, 720, "CSC126 Mini Project", NULL, NULL);
	if (!window)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	return 0;
}

void render::imguiinit()
{
	ImGui::CreateContext();
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