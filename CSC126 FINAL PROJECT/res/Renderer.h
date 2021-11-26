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
	bool home = true;
	bool createtable = false;
	bool opentable = false;
	bool debug = false;

	void menubar();
	void debug_mode(bool* open);
	void homepage(bool* open);

	// Table stuff
	void tablecreation(bool* open);
	void table(bool* open);

	char name[20] = "Default Table Name";
	char namenow[20] = "Default name";
	float spacingVertical = 0;
	float spacingHorizontal = -1;
	ImVec4 TableWindowColorSpace = { .45f, .6f, .7f, 1.0f };
	ImVec4 TableBgColorSpace = {.6f, .69f, .75f, 2.0f };
	ImVec4 TableLineColorSpace = { .45f, .55f, .6f, 1.0f };
	ImGuiID tableopenarea = 12099;
	ImGuiID dragresizableArea = 12098;
private:
	// Shorting Helper Functions
	void t_horizon(int h);
	void t_vertical(int h);

	// MENU BAR
	bool customization = false;

	void TableModeBar();
	void customize(bool* open, ImVec4& data, const char* whichWindow);

	// INITIALIZATION
	void imguiinit();
	int glfwinit();
	void colorinitialization();
	static void glfw_error_callback(int error, const char* description);

	// WINDOW RELATED
	const char* glsl_version = "#version 130";
	GLFWwindow* window = NULL;
	ImGuiIO io;

private:
	// DEBUGGING
	// FRAME RELATED
	int width = 0, height = 0;
	ImVec4 clear;
	ImVec2 size = ImVec2(200,200);

	// FPS RELATED
	double lasttime = 0;
	int FPS_LIMIT = 60;
	int FPS_HOLDER = 60;
	bool enable = false;
	int count = 0;
	float t = 0;
	int offset = 0;
	ImVector<ImVec2> datax{};

	void FPS_limit(int fps);
	void fpsgraph();

	// CONSOLE LIKE
	ImGuiID consoling;
};