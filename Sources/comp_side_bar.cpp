#include "main.h"
#include "comp_side_bar.h"

namespace SideBar
{
   void RenderComponent(bool* p_open)
   {
      // the axis will always be X for the ToolBar
      ImGuiAxis toolbar_axis = ImGuiAxis_Y;

      // We request auto-sizing on one axis.
      // This will only affect the toolbar when NOT docked
      ImGui::SetNextWindowSize(ImVec2(0.0f, -1.0f));

      // Specific docking options for toolbars.

      // Currently they add some constraint we ideally wouldn't want, 
      // but this is simplifying our first implementation
      ImGuiWindowClass window_class;

      window_class.DockingAllowUnclassed = true;

      window_class.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_NoCloseButton;
      window_class.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_HiddenTabBar;
      window_class.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_NoDockingSplit;
      window_class.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_NoDockingOverMe;
      window_class.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_NoDockingOverOther;
      window_class.DockNodeFlagsOverrideSet |= ImGuiDockNodeFlags_NoResizeX;

      ImGui::SetNextWindowClass(&window_class);

      // Set window flags
      ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoCollapse;
      window_flags |= ImGuiWindowFlags_NoTitleBar;
      window_flags |= ImGuiWindowFlags_NoScrollbar;

      // Set font size
      const float font_size = ImGui::GetFontSize();
      const ImVec2 icon_size(ImFloor(font_size * 1.7f) * 2.5f, ImFloor(font_size * 1.7f) * 2.5f);

      // Make the background the same color as the title bar
      ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.09f, 0.10f, 0.15f, 1.00f));

      // Begin into the window
      ImGui::Begin(I18("Side Bar"), p_open, window_flags);

      ImGui::PopStyleColor();

      // Overwrite node size
      ImGuiDockNode* node = ImGui::GetWindowDockNode();

      if (node != NULL)
      {
         // Overwrite size of the node
         ImGuiStyle& style = ImGui::GetStyle();

         const ImGuiAxis toolbar_axis_perp = (ImGuiAxis)(ImGuiAxis_Y ^ 1);
         node->Size[toolbar_axis_perp] = node->SizeRef[toolbar_axis_perp] = 
            style.WindowPadding[toolbar_axis_perp] * 2.0f + icon_size[toolbar_axis_perp];

         node->WantLockSizeOnce = true;

         if (node->ParentNode && node->ParentNode->SplitAxis != ImGuiAxis_None)
         {
            toolbar_axis = (ImGuiAxis)(node->ParentNode->SplitAxis ^ 1);
         }
      }

      // Populate tab bar
      ImGui::PushStyleVar(ImGuiStyleVar_FrameRounding, 3.0f);
      ImGui::PushStyleVar(ImGuiStyleVar_ItemSpacing, ImVec2(5.0f, 5.0f));

      ImGui::Button(ICON_FA_COPY, icon_size);
      if (ImGui::IsItemHovered())
      {
         ImGui::BeginTooltip();
         ImGui::Text("Explorer");
         ImGui::EndTooltip();
      }

      ImGui::Button(ICON_FA_SEARCH, icon_size);
      if (ImGui::IsItemHovered())
      {
         ImGui::BeginTooltip();
         ImGui::Text("Search");
         ImGui::EndTooltip();
      }

      ImGui::Button(ICON_FA_CODE_BRANCH, icon_size);
      if (ImGui::IsItemHovered())
      {
         ImGui::BeginTooltip();
         ImGui::Text("Source Control");
         ImGui::EndTooltip();
      }

      ImGui::Button(ICON_FA_BUG, icon_size);
      if (ImGui::IsItemHovered())
      {
         ImGui::BeginTooltip();
         ImGui::Text("Run with Debug");
         ImGui::EndTooltip();
      }

      ImGui::Button(ICON_FA_BARS, icon_size);
      if (ImGui::IsItemHovered())
      {
         ImGui::BeginTooltip();
         ImGui::Text("Extensions");
         ImGui::EndTooltip();
      }

      ImGui::PopStyleVar(2);

      // End window
      ImGui::End();
   }
}