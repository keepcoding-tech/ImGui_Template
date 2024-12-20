#include "comp_side_bar.h"
#include "comp_tool_bar.h"
#include "window_about.h"
#include "window_change_log.h"
#include "window_main.h"
#include "window_modal.h"
#include "window_preferences.h"

namespace WindowMain
{
   void RenderMainMenuBar();

   // Stored window data
   struct WindowMainData window_data;

   void RenderMainWindow()
   {
      // Exceptionally add an extra assert here for people confused about 
      // initial Dear ImGui setup. Most functions would normally just 
      // assert/crash if the context is missing.
      IM_ASSERT(ImGui::GetCurrentContext() != NULL && "Missing Dear ImGui context!");

      // Verify ABI compatibility between caller code and compiled version of 
      // Dear ImGui. This helps detects some build issues.
      IMGUI_CHECKVERSION();

      // +---------------------------------------------------------------------+
      // | [SECTION] Main Window Dockspace                                     |
      // +---------------------------------------------------------------------+

      // We are using the ImGuiWindowFlags_NoDocking flag to make the parent 
      // window not dockable into, because it would be confusing to have two 
      // docking targets within each others.
      ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoDocking;

      // add the rest of the flags to the dockspace
      window_flags |= ImGuiWindowFlags_MenuBar;
      window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse;
      window_flags |= ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
      window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus;

      const ImGuiViewport* viewport = ImGui::GetMainViewport();
      ImGui::SetNextWindowPos(viewport->WorkPos);
      ImGui::SetNextWindowSize(viewport->WorkSize);
      ImGui::SetNextWindowViewport(viewport->ID);

      ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);

      ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));

      // Main body of the MainWindow starts here
      if (ImGui::Begin("Dock Space", NULL, window_flags) == false)
      {
        // Early out if the window is 
        // collapsed, as an optimization
        ImGui::End();

        return;
      }

      ImGui::PopStyleVar();
      ImGui::PopStyleVar(2);

      // Submit the DockSpace
      ImGuiIO& io = ImGui::GetIO();
      if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
      {
         ImGuiID dockspace_id = ImGui::GetID("MainWindowDockspace");
         ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), ImGuiDockNodeFlags_None);
      }

      // +---------------------------------------------------------------------+
      // | [SECTION] Main Window Menu Bar                                      |
      // +---------------------------------------------------------------------+

      RenderMainMenuBar();

      if (window_data.OpenPreferences == true)
      {
         WindowPreferences::RenderWindow(&window_data.OpenPreferences);
      }

      if (window_data.ShowToolBar == true)
      {
         ToolBar::RenderComponent(&window_data.ShowToolBar);
      }

      if (window_data.ShowSideBar == true)
      {
         SideBar::RenderComponent(&window_data.ShowSideBar);
      }

#ifdef _DEBUG
      if (window_data.ShowDebugLog == true)
      {
         ImGui::ShowDebugLogWindow(&window_data.ShowDebugLog);
      }

      if (window_data.ShowDemoWindow == true)
      {
         ImGui::ShowDemoWindow();
      }
#endif

      if (window_data.ShowChangeLogWindow == true)
      {
         WindowChangeLog::RenderWindow(&window_data.ShowChangeLogWindow);
      }

      if (window_data.ShowAboutWindow == true)
      {
         WindowAbout::RenderWindow(&window_data.ShowAboutWindow);
      }

      // +---------------------------------------------------------------------+
      // | [SECTION] Warning & Error Modals                                    |
      // +---------------------------------------------------------------------+

      if (Main_ShowExitModal == true)
      {
         // show modal window
         int modal_ret = WindowModal::WarningModal(
            I18("Exit Application"),
            I18("Are you sure you want to exit the application?"),
            &Main_ShowExitModal,
            NULL,
            KcWindowModalFlags_WarningIcon | 
            KcWindowModalFlags_YesButton | 
            KcWindowModalFlags_CancelButton
         );

         // close the application if pressed 'Yes'
         if (modal_ret == KcWindowModalFlags_YesButton)
         {
            Main_CloseApplication();
         }
      }
      
      // End of the MainWindow
      ImGui::End();
   }

   //-------------------------------------------------------------------------//

   void RenderMainMenuBar()
   {
      // Style the menu bar and the menu items
      ImGuiStyle& style = ImGui::GetStyle();

      style.PopupRounding = 4;
      style.ItemSpacing = ImVec2(16.0f, 8.0f);
      style.FramePadding.y = 10.0f;

      // MenuBar
      if (ImGui::BeginMenuBar())
      {
         // MenuBar -> File
         if (ImGui::BeginMenu(I18("File")))
         {
            // MenuBar -> File -> Preferences
            if (ImGui::MenuItem(I18("Preferences")))
            {
               window_data.OpenPreferences = true;
            }

            ImGui::Separator();

            // MenuBar -> File -> Exit
            if (ImGui::MenuItem(I18("Exit"), "Alt+F4"))
            {
               Main_ShowExitModal = true;
            }

            ImGui::EndMenu();
         }

         // MenuBar -> View
         if (ImGui::BeginMenu(I18("View")))
         {
            // MenuBar -> View -> Full Screen
            if (ImGui::MenuItem(I18("Full Screen"), "F11"))
            {
               Main_ToggleFullscreen();
            }

            ImGui::Separator();

            // MenuBar -> View -> Tool Bar
            if (ImGui::MenuItem(I18("Tool Bar"), NULL, &window_data.ShowToolBar)) {}
            // MenuBar -> View -> Explorer
            if (ImGui::MenuItem(I18("Side Bar"), NULL, &window_data.ShowSideBar)) {}

            ImGui::Separator();

            if (ImGui::BeginMenu(I18("Tools")))
            {

#ifdef _DEBUG
               // MenuBar -> View -> Debug Log
               if (ImGui::MenuItem(I18("Debug Log"), NULL, &window_data.ShowDebugLog)) {}

               // MenuBar -> View -> Demo Window
               if (ImGui::MenuItem(I18("Demo Window"), NULL, &window_data.ShowDemoWindow)) {}
#endif

               ImGui::EndMenu();
            }

            ImGui::EndMenu();
         }
         
         // MenuBar -> Help
         if (ImGui::BeginMenu(I18("Help")))
         {
            // MenuBar -> Help -> Change Log
            if (ImGui::MenuItem(I18("Change Log")))
            {
               window_data.ShowChangeLogWindow = 
                  !window_data.ShowChangeLogWindow;
            }

            // MenuBar -> Help -> About
            if (ImGui::MenuItem(I18("About")))
            {
               window_data.ShowAboutWindow = 
                  !window_data.ShowAboutWindow;
            }

            ImGui::EndMenu();
         }

         ImGui::EndMenuBar();
      }
   }

   //-------------------------------------------------------------------------//
}