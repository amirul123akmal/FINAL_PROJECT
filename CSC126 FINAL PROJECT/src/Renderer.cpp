#include "Renderer.h"

int render::runMainProcess()
{
	while (!glfwWindowShouldClose(window))
	{
		// Set New Frame
		glfwPollEvents();
		new_frame();

		// Frame body
		// ImGui::ShowDemoWindow((bool*)1); // Demo
		ImGui::Begin("Hello World");
		size = ImGui::GetWindowSize();
		ImGui::SetWindowSize(size);

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
	window = glfwCreateWindow(1280, 720, "ImGui with OpenGl3", NULL, NULL);
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