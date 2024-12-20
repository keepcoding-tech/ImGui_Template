#include "main.h"

#include "window_about.h"

namespace WindowAbout
{
   void RenderWindow(bool* p_open)
   {
      ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;
      flags |= ImGuiWindowFlags_NoDocking;

      // Open window
      if (ImGui::Begin(I18("About"), p_open, flags) == false)
      {
         ImGui::End();
         return;
      }

      // Application version
      ImGui::Text("keepcoding %s WIP (%d)", KC_VERSION, KC_VERSION_BN);

      // Important links
      ImGui::TextLinkOpenURL(I18("Homepage"), "https://github.com/keepcoding-tech");
      ImGui::SameLine();
      ImGui::TextLinkOpenURL(I18("LICENSE"), "https://mit-license.org/");

      ImGui::Separator();

      // Author(s)
      ImGui::Text(I18("By keepcoding.tech with the help of Dear ImGui."));

      ImGui::NewLine();

      // License
      ImGui::Text(I18("This application is open - source and distributed under the MIT license,"));
      ImGui::Text(I18("promoting freedom and collaboration among developers."));
      ImGui::Text(I18("See LICENSE for more information."));

      ImGui::NewLine();

      // Funding
      ImGui::Text(I18("If your are using this, please consider funding the project."));

      // Config and Build info
      static bool show_config_info = false;
      ImGui::Checkbox(I18("Config/Build Information"), &show_config_info);

      if (show_config_info)
      {
         // Copy to clipboard button
         bool copy_to_clipboard = ImGui::Button(I18("Copy to clipboard"));

         ImVec2 child_size = ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 18);
         ImGui::BeginChild(ImGui::GetID("cfg_infos"), child_size, ImGuiChildFlags_FrameStyle);

         // Style the config info as "code"
         if (copy_to_clipboard)
         {
            ImGui::LogToClipboard();
            ImGui::LogText("```\n");
         }

         // Dear ImGui version
         ImGui::Text("Dear ImGui %s (%d)", IMGUI_VERSION, IMGUI_VERSION_NUM);

         ImGui::Separator();

         // Variable size
         ImGui::Text("sizeof(size_t): %d, ", (int)sizeof(size_t));
         ImGui::SameLine();
         ImGui::Text("sizeof(ImDrawIdx): %d, ", (int)sizeof(ImDrawIdx));
         ImGui::SameLine();
         ImGui::Text("sizeof(ImDrawVert): %d", (int)sizeof(ImDrawVert));

         ImGui::Text("define: __cplusplus=%d", (int)__cplusplus);

#ifdef _WIN32
         ImGui::Text("define: _WIN32");
#endif
#ifdef _WIN64
         ImGui::Text("define: _WIN64");
#endif
#ifdef __linux__
         ImGui::Text("define: __linux__");
#endif
#ifdef __APPLE__
         ImGui::Text("define: __APPLE__");
#endif
#ifdef _MSC_VER
         ImGui::Text("define: _MSC_VER=%d", _MSC_VER);
#endif
#ifdef _MSVC_LANG
         ImGui::Text("define: _MSVC_LANG=%d", (int)_MSVC_LANG);
#endif
#ifdef __MINGW32__
         ImGui::Text("define: __MINGW32__");
#endif
#ifdef __MINGW64__
         ImGui::Text("define: __MINGW64__");
#endif
#ifdef __GNUC__
         ImGui::Text("define: __GNUC__=%d", (int)__GNUC__);
#endif
#ifdef __clang_version__
         ImGui::Text("define: __clang_version__=%s", __clang_version__);
#endif
#ifdef __EMSCRIPTEN__
         ImGui::Text("define: __EMSCRIPTEN__");
         ImGui::Text("Emscripten: %d.%d.%d", __EMSCRIPTEN_major__, __EMSCRIPTEN_minor__, __EMSCRIPTEN_tiny__);
#endif
#ifdef IMGUI_HAS_VIEWPORT
         ImGui::Text("define: IMGUI_HAS_VIEWPORT");
#endif
#ifdef IMGUI_HAS_DOCK
         ImGui::Text("define: IMGUI_HAS_DOCK");
#endif

         if (copy_to_clipboard)
         {
            ImGui::LogText("\n```\n");
            ImGui::LogFinish();
         }

         ImGui::EndChild();
      }

      // End Window
      ImGui::End();
   }
}
