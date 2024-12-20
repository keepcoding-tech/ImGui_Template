#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "window_main.h"
#include "window_modal.h"

#include "font_awesome.cpp"
#include "font_awesome.h"

#include <stdio.h>

#define GL_SILENCE_DEPRECATION
#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <GLES2/gl2.h>
#endif

#include <GLFW/glfw3.h>

#if defined(_MSC_VER) && (_MSC_VER >= 1900) && !defined(IMGUI_DISABLE_WIN32_FUNCTIONS)
#pragma comment(lib, "legacy_stdio_definitions")
#pragma comment(lib, "Dwmapi")
#endif

#ifdef __EMSCRIPTEN__
#include "../libs/emscripten/emscripten_mainloop_stub.h"
#endif

#define GLFW_EXPOSE_NATIVE_WIN32
#define GLFW_EXPOSE_NATIVE_WGL
#define GLFW_NATIVE_INCLUDE_NONE

#include <GLFW/glfw3native.h>
#include <dwmapi.h>


// --- MARK: PRIVATE GLOBAL MEMBERS ----------------------------------------  //

GLFWwindow*  window  = nullptr;
GLFWmonitor* monitor = nullptr;

int windowed_x      = 0;
int windowed_y      = 0;
int windowed_width  = 0;
int windowed_height = 0;

bool is_fullscreen   = false;

bool Main_ShowExitModal = false;

// --- MARK: PRIVATE FUNCTIONS ---------------------------------------------- //

static void glfw_error_callback(int error, const char* description);
static void glfw_close_callback(GLFWwindow* window);
static bool IsDarkModeEnabled(GLFWwindow* window);

//----------------------------------------------------------------------------//

int main(int, char**)
{
   // asign error callback
   glfwSetErrorCallback(glfw_error_callback);

   // init GLFW
   if (!glfwInit())
   {
      return 1;
   }

   // Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
   const char* glsl_version = "#version 100";
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
   const char* glsl_version = "#version 150";
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
   const char* glsl_version = "#version 130";
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
   //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
   //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    //glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

    // Create window with graphics context
    window = glfwCreateWindow(1280, 720,
      "Dear ImGui GLFW + OpenGL3", nullptr, nullptr);

   if (window == nullptr)
   {
      return 1;
   }

   // Set the window close callback
   glfwSetWindowCloseCallback(window, glfw_close_callback);

   glfwMakeContextCurrent(window);
   glfwSwapInterval(1); // Enable vsync

   // Setup Dear ImGui context
   IMGUI_CHECKVERSION();
   ImGui::CreateContext();
   ImGuiIO& io = ImGui::GetIO(); (void)io;
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
   io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
   io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
   io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
   //io.ConfigViewportsNoAutoMerge = true;
   //io.ConfigViewportsNoTaskBarIcon = true;

   // Setup Dear ImGui style
   if (IsDarkModeEnabled(window))
   {
      //ImGui::StyleColorsDark();
      ImGui::StyleColorsKeepcoding();
   }
   else
   {
      ImGui::StyleColorsLight();
   }

   // When viewports are enabled we tweak WindowRounding/WindowBg
   // so platform windows can look identical to regular ones.
   ImGuiStyle& style = ImGui::GetStyle();
   if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
   {
      style.WindowRounding = 0.0f;
      style.Colors[ImGuiCol_WindowBg].w = 1.0f;
   }

   // Setup Platform/Renderer backends
   ImGui_ImplGlfw_InitForOpenGL(window, true);
#ifdef __EMSCRIPTEN__
   ImGui_ImplGlfw_InstallEmscriptenCallbacks(window, "#canvas");
#endif
   ImGui_ImplOpenGL3_Init(glsl_version);


   // +------------------------------------------------------------------------+
   // | [SECTION] FONTS & ICONS                                                |
   // +------------------------------------------------------------------------+

   // Set main font
   io.Fonts->AddFontDefault();

   ImFontConfig font_config;
   font_config.FontDataOwnedByAtlas = false;

   //io.Fonts->AddFontFromFileTTF("c:\\Windows\\Fonts\\segoeui.ttf", 16.0f, &font_config);

   font_config.MergeMode = true;
   //font_config.PixelSnapH = true;
   font_config.GlyphMinAdvanceX = 13.0f;
   font_config.GlyphOffset = ImVec2(0.0f, 8.0f);
   //font_config.OversampleH = 3;
   //font_config.OversampleV = 3;
   //font_config.GlyphMinAdvanceX = 30.0f;

   // Configure the icons from memory
   static const ImWchar icon_ranges[]{ ICON_MIN_FA, ICON_MAX_FA, 0 };

   // Add the Icons font
   io.Fonts->AddFontFromMemoryCompressedTTF(
      font_awesome_data, font_awesome_size, 30.0f, &font_config, icon_ranges
   );

   font_config.GlyphMinAdvanceX = 0.0f;


   // Merge the fonts
   io.Fonts->Build();


   // Our state
   ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

   // Main loop
#ifdef __EMSCRIPTEN__
    // For an Emscripten build we are disabling file-system access, so let's 
    // not attempt to do a fopen() of the imgui.ini file.
    // You may manually call LoadIniSettingsFromMemory() to load settings 
    // from your own storage.
   io.IniFilename = nullptr;
   EMSCRIPTEN_MAINLOOP_BEGIN
#else
   while (!glfwWindowShouldClose(window))
#endif
   {
      // Poll and handle events (inputs, window resize, etc.)
      glfwPollEvents();
      if (glfwGetWindowAttrib(window, GLFW_ICONIFIED) != 0)
      {
         ImGui_ImplGlfw_Sleep(10);
         continue;
      }

      // Start the Dear ImGui frame
      ImGui_ImplOpenGL3_NewFrame();
      ImGui_ImplGlfw_NewFrame();
      ImGui::NewFrame();


      // +---------------------------------------------------------------------+
      // | [SECTION] HERE STARTS THE APPLICATION                               |
      // +---------------------------------------------------------------------+

      WindowMain::RenderMainWindow();


      // Toggle fullscreen if F11 
      // key has been pressed
      if (glfwGetKey(window, GLFW_KEY_F11) == GLFW_PRESS)
      {
         Main_ToggleFullscreen();
      }

      // Rendering
      ImGui::Render();

      // Get fram buffer size
      int display_w, display_h;
      glfwGetFramebufferSize(window, &display_w, &display_h);

      glViewport(0, 0, display_w, display_h);

      // Paint the background of the GLFW window
      glClearColor(
         clear_color.x * clear_color.w, 
         clear_color.y * clear_color.w,
         clear_color.z * clear_color.w, 
         clear_color.w
      );
      glClear(GL_COLOR_BUFFER_BIT);

      // Draw data to the window
      ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

      // Update and Render additional Platform Windows
      if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
      {
         GLFWwindow* backup_current_context = glfwGetCurrentContext();
         ImGui::UpdatePlatformWindows();
         ImGui::RenderPlatformWindowsDefault();
         glfwMakeContextCurrent(backup_current_context);
      }

      glfwSwapBuffers(window);
   }
#ifdef __EMSCRIPTEN__
   EMSCRIPTEN_MAINLOOP_END;
#endif

   // Cleanup
   ImGui_ImplOpenGL3_Shutdown();
   ImGui_ImplGlfw_Shutdown();
   ImGui::DestroyContext();

   glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}

//----------------------------------------------------------------------------//

void Main_CloseApplication()
{
   // Shutdow the entire application
   glfwSetWindowShouldClose(window, GLFW_TRUE);
}

//----------------------------------------------------------------------------//

void Main_ToggleFullscreen()
{
   // Restore windowed mode
   if (is_fullscreen == true)
   {
      glfwSetWindowMonitor(window, nullptr, windowed_x, windowed_y,
         windowed_width, windowed_height, 0);
   }
   else
   {
      // Save current window position and size
      glfwGetWindowPos(window, &windowed_x, &windowed_y);
      glfwGetWindowSize(window, &windowed_width, &windowed_height);

      // Get monitor and its resolution
      monitor = glfwGetPrimaryMonitor();
      const GLFWvidmode* mode = glfwGetVideoMode(monitor);

      // Set fullscreen
      glfwSetWindowMonitor(window, monitor, 0, 0, 
         mode->width, mode->height, mode->refreshRate);
   }

   // Toggle the fullscreen state
   is_fullscreen = !is_fullscreen;
}

//----------------------------------------------------------------------------//

static void glfw_error_callback(int error, const char* description)
{
   fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

//----------------------------------------------------------------------------//

static void glfw_close_callback(GLFWwindow* window)
{
   // Prevent GLFW from automatically closing the window
   glfwSetWindowShouldClose(window, GLFW_FALSE);

   Main_ShowExitModal = true;
}

//----------------------------------------------------------------------------//

static bool IsDarkModeEnabled(GLFWwindow* window) {
#if defined(__APPLE__)
   // TODO: add darkmode window for Mac

#else // (WINDOWS)

   DWORD value = 0;
   DWORD valueSize = sizeof(value);

   HKEY hKey;

   // Open the registry key
   if (RegOpenKeyEx(HKEY_CURRENT_USER,
      L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
      0, KEY_READ, &hKey) == ERROR_SUCCESS)
   {
      if (RegQueryValueEx(hKey, L"AppsUseLightTheme", nullptr, nullptr,
         (LPBYTE)&value, &valueSize) == ERROR_SUCCESS)
      {
         RegCloseKey(hKey);

         // 0 means dark mode
         if (value == 0)
         {
            // make GLFW window bar darkmode
            BOOL pvAttribute = true;
            DwmSetWindowAttribute(
               glfwGetWin32Window(window),
               DWMWA_USE_IMMERSIVE_DARK_MODE,
               &pvAttribute, sizeof(pvAttribute)
            );
         }

         return value == 0;
      }

      RegCloseKey(hKey);
   }

   // default to Light Mode
   return false;
#endif
}

//----------------------------------------------------------------------------//

