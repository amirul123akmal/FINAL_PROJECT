#include "Basics.h"
#include "table.h"

#define opengl_newframe ImGui_ImplOpenGL3_NewFrame()
#define glfw_newframe ImGui_ImplGlfw_NewFrame()
#define imgui_newframe ImGui::NewFrame()
#define new_frame() opengl_newframe;glfw_newframe;imgui_newframe

#define imggl_render(x) ImGui_ImplOpenGL3_RenderDrawData(x)

class render : public json_table
{
public:
	render();
	
	void initall();
	int runMainProcess();

	~render();

private:
	bool exit = false;
	bool createtable = false;
	bool opentable = false;

	void homepage();
	void table(bool* open);
	void tablecreation(bool* open);

private:
	void imguiinit();
	int glfwinit();
	static void glfw_error_callback(int error, const char* description);
private:
	// Window Stuff
	const char* glsl_version = "#version 130";
	GLFWwindow* window = NULL;
	ImGuiIO io;

	// Frame stuff
	int width = 0, height = 0;
	ImVec4 clear = ImVec4(.45f, .55f, .6f, 1.0f);
	ImVec2 size = ImVec2(200,200);
};