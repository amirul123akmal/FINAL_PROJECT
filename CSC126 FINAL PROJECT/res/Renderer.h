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
	ImVec4 TableWindowColorSpace; // TbWinColSpa
	ImVec4 TableBgColorSpace;	  // TbBgColSpa
	ImVec4 TableLineColorSpace = { .45f, .55f, .6f, 1.0f };	 
	ImGuiID TableBgColor_Space = 12100;
	ImGuiID tableopenarea = 12099;
	ImGuiID dragresizableArea = 12098;
private:
	// DOCKING
	ImGuiID dockingID = 123456789;

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
	static void glfw_error_callback(int error, const char* description);

	// COLOR
	void colorinitialization(ImVec4& Vec4ColSpace, const char*);
	void initializecolorspace();
	bool colorWindowWasOpen = false;

	// WINDOW RELATED
	const char* glsl_version = "#version 130";
	GLFWwindow* window = NULL;
	ImGuiIO io;

private:
	// ===================
	///DEBUGGING
	// ===================
	// FRAME RELATED
	int width = 0, height = 0;
	ImVec4 clear;
	ImVec2 size = ImVec2(200,200);

	// FPS RELATED
	double lasttime = 0;
	int FPS_LIMIT = 60;
	bool enable = false;
	int count = 0;

	void FPS_limit(int fps);
	
	// GRAPH
	ImGuiID graphID = 1234567;
	ImVector<ImVec2> datax{};
	int offset = 0;
	float t = 0;
	float t_c = 0;
	float h = 0;
	
	void graph();

	// CONSOLE LIKE
	ImGuiID DebuggingFrame1 = 123;
	std::vector < std::string > ConsoleText{"Color setting Loaded", "Table saved loaded"};
	std::vector<bool> tracker{};
	void trackerinit();
	void captureMouseClickSafety();
	void ConsoleUpdate();

};