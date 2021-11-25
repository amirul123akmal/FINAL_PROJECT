#pragma once

// External Lib Header
// All commeneted out include(s) will be un-comment when in needed
// #include "boost/asio/thread_pool.hpp"
// #include "boost/asio/post.hpp"
#include "nlohmann/json.hpp"
#include "spdlog/spdlog.h"

// GUI Stuff
#include "GLFW/glfw3.h"
#include "imgui/imgui.h"
#include "implot.h"
#include "implot_internal.h"
#include "imgui/backends/imgui_impl_opengl3.h"
#include "imgui/backends/imgui_impl_glfw.h"
#include <tchar.h>


// STL
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <filesystem>
#include <mutex>
#include <chrono>

// Headers
#include "Definitive.h"