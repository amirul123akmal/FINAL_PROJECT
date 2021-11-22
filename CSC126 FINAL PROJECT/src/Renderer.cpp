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
		if (home) { homepage(&home); }
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
void render::homepage(bool* enable)
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
	}
}

void render::table(bool* open)
{
	int count = 8;
	if (ImGui::Begin("Table", open))
	{
		if (ImGui::CollapsingHeader("Table List"))
		{
			ImGui::Text("Hari / Masa");
			ImGui::Text("Hari / Masa");
			ImGui::Text("Hari / Masa");
			ImGui::Text("Hari / Masa");
			ImGui::Text("Hari / Masa");
			ImGui::Text("Hari / Masa");
			ImGui::Text("Hari / Masa");
		}

		if (ImGui::BeginTable("Jadual", 16))
		{
			ImGui::TableNextRow();
			ImGui::TableSetColumnIndex(0);
			ImGui::Text("Hari / Masa");
			for (int column = 1; column < 16; column++)
			{
				ImGui::TableSetColumnIndex(column);
				ImGui::Text("%d:00",count++);
			}
			ImGui::EndTable();
		}
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
	glfwSwapInterval(0);
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