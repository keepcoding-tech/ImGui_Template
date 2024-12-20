#include "window_change_log.h"

#include "main.h"

namespace WindowChangeLog
{
   void RenderWindow(bool* p_open)
   {
      ImGuiWindowFlags flags = ImGuiWindowFlags_AlwaysAutoResize;

      // Open window
      if (ImGui::Begin(I18("Change Log"), p_open, flags) == false)
      {
         ImGui::End();
         return;
      }

      //----------------------------------------------------------------------//

      // Header Section
      ImGui::Text("December 2024 (version 1.1.0)");

      ImGui::Separator();

      ImGui::TextWrapped(
         "Welcome to the December 2024 release of ImGui_Template.\n"
         "This version introduces several exciting updates we hope you'll enjoy.\n"
         "Key highlights include :"
      );

      ImGui::Spacing();
      ImGui::Spacing();

      ImGui::BulletText("Debug Log and Demo Window added for debug builds");
      ImGui::BulletText("New preferences for customizing language and themes");
      ImGui::BulletText("Toolbar and sidebar functionality implemented");
      ImGui::BulletText("Main window menu bar added");
      ImGui::BulletText("Docking feature introduced for the main window");

      ImGui::Separator();

      ImGui::Spacing();
      ImGui::Spacing();

      //----------------------------------------------------------------------//

      // Header Section
      ImGui::Text("November 2024 (version 1.0.0)");

      ImGui::Separator();

      ImGui::TextWrapped("This version provides the foundational features, including:");

      ImGui::Spacing();
      ImGui::Spacing();

      ImGui::BulletText("Support for multiple fonts, including icon sets");
      ImGui::BulletText("Automatic detection of OS theme preferences (dark/light)");
      ImGui::BulletText("Preconfigured setup for ImGui, OpenGL, and GLFW");
      ImGui::BulletText("Organized project structure for streamlined development");

      ImGui::Separator();

      ImGui::Spacing();
      ImGui::Spacing();

      //----------------------------------------------------------------------//

      // Footer Section
      ImGui::Text("Realized by - ");
      ImGui::SameLine();
      ImGui::TextColored(ImVec4(0.8f, 0.8f, 0.8f, 1.0f), "keepcoding.tech");

      // End Window
      ImGui::End();
   }
}
