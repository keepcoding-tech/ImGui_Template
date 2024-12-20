#include "main.h"
#include "window_modal.h"

namespace WindowModal
{
   KcWindowModalFlags RenderWindow(const char* title, const char* message, 
      const char* more_text, bool* p_open, KcWindowModalFlags flags)
   {
      // toggle the 'more' and 'less' button
      static bool show_more_text = false;

      // This will opne the popup window
      ImGui::OpenPopup(title);

      // Always center this window when appearing
      ImVec2 center = ImGui::GetMainViewport()->GetCenter();
      ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f));
      ImGui::SetNextWindowSize(ImVec2(400.0f, 0.0f));

      // Begin the modal window
      if (ImGui::BeginPopupModal(title, p_open, ImGuiWindowFlags_AlwaysAutoResize))
      {
         // Display error icon
         if (flags & KcWindowModalFlags_ErrorIcon)
         {
            ImGui::Spacing();
            ImGui::Spacing();

            // red error icon
            ImGui::TextColored(
               ImVec4(1.0f, 0.2f, 0.2f, 1.0f), 
               ICON_FA_BAN
            );

            ImGui::SameLine();
         }

         // Display warning icon
         if (flags & KcWindowModalFlags_WarningIcon)
         {
            ImGui::Spacing();
            ImGui::Spacing();

            // yellow warning icon
            ImGui::TextColored(
               ImVec4(1.0f, 0.6f, 0.2f, 1.0f), 
               ICON_FA_EXCLAMATION_CIRCLE
            );

            ImGui::SameLine();
         }

         // Display info icon
         if (flags & KcWindowModalFlags_InfoIcon)
         {
            ImGui::Spacing();
            ImGui::Spacing();

            // blue information icon
            ImGui::TextColored(
               ImVec4(0.0667f, 0.4667f, 0.7333f, 1.0f),
               ICON_FA_INFO_CIRCLE
            );

            ImGui::SameLine();
         }

         // Wrap the text arond
         ImGui::TextWrapped(message);

         ImGui::Separator();

         // Make sure there is a 'more_text'
         if (more_text != NULL && strlen(more_text) > 0)
         {
            // Display 'more' button
            if (ImGui::Button(I18(show_more_text ? "Less" : "More")))
            {
               show_more_text = !show_more_text;
            }

            if (show_more_text == true)
            {
               // Begin child window
               ImGui::BeginChild(
                  ImGui::GetID("more_text"), 
                  ImVec2(0, ImGui::GetTextLineHeightWithSpacing() * 3),
                  ImGuiChildFlags_FrameStyle
               );

               // display the more text
               ImGui::TextWrapped(more_text);

               // End child window
               ImGui::EndChild();
            }
         }

         ImGui::Spacing();
         ImGui::Spacing();

         ImGui::SetItemDefaultFocus();

         // Center the buttons in the window
         int buttonCount = 0;

         if (flags & KcWindowModalFlags_YesButton)    ++buttonCount;
         if (flags & KcWindowModalFlags_NoButton)     ++buttonCount;
         if (flags & KcWindowModalFlags_OKButton)     ++buttonCount;
         if (flags & KcWindowModalFlags_CancelButton) ++buttonCount;

         if (buttonCount > 0)
         {
            // Calculate total width
            float totalWidth = (60.0f * buttonCount) + 
               (ImGui::GetStyle().ItemSpacing.x * (buttonCount - 1));

            // Apply the horizontal offset
            ImGui::SetCursorPosX(ImGui::GetCursorPosX() + 
               (ImGui::GetContentRegionAvail().x - totalWidth) * 0.5f);
         }

         // Display 'Yes' button
         if (flags & KcWindowModalFlags_YesButton)
         {
            if (ImGui::Button(I18("Yes"), ImVec2(60, 0)))
            {
               *p_open = false;

               ImGui::EndPopup();

               return KcWindowModalFlags_YesButton;
            }
         }

         // Display 'No' button
         if (flags & KcWindowModalFlags_NoButton)
         {
            ImGui::SameLine();

            // Get the default button background color
            ImVec4 defaultButtonColor = ImGui::GetStyleColorVec4(ImGuiCol_Button);

            // 'No' will allways have a "secondary" button style
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_Border, defaultButtonColor);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);

            if (ImGui::Button(I18("No"), ImVec2(60, 0)))
            {
               *p_open = false;

               ImGui::PopStyleVar();
               ImGui::PopStyleColor(2);

               ImGui::EndPopup();

               return KcWindowModalFlags_NoButton;
            }

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);
         }

         // Display 'OK' button
         if (flags & KcWindowModalFlags_OKButton)
         {
            ImGui::SameLine();

            if (ImGui::Button(I18("OK"), ImVec2(60, 0)))
            {
               *p_open = false;

               ImGui::EndPopup();

               return KcWindowModalFlags_OKButton;
            }
         }

         // Display 'Cancel' button
         if (flags & KcWindowModalFlags_CancelButton)
         {
            ImGui::SameLine();

            // Get the default button background color
            ImVec4 defaultButtonColor = ImGui::GetStyleColorVec4(ImGuiCol_Button);

            // 'Cancel' will allways have a "secondary" button style
            ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0, 0, 0, 0));
            ImGui::PushStyleColor(ImGuiCol_Border, defaultButtonColor);
            ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 2.0f);

            if (ImGui::Button(I18("Cancel"), ImVec2(60, 0)))
            {
               *p_open = false;

               ImGui::PopStyleVar();
               ImGui::PopStyleColor(2);

               ImGui::EndPopup();

               return KcWindowModalFlags_CancelButton;
            }

            ImGui::PopStyleVar();
            ImGui::PopStyleColor(2);
         }

         ImGui::EndPopup();
      }

      return KcWindowModalFlags_None;
   }

   //-------------------------------------------------------------------------//

   KcWindowModalFlags ErrorModal(const char* title, const char* message, 
      bool* p_open, const char* more_text, KcWindowModalFlags flags)
   {
      return RenderWindow(title, message, more_text, p_open, flags != 0 ? flags 
         : KcWindowModalFlags_ErrorIcon | KcWindowModalFlags_OKButton);
   }

   //-------------------------------------------------------------------------//

   KcWindowModalFlags WarningModal(const char* title, const char* message, 
      bool* p_open, const char* more_text, KcWindowModalFlags flags)
   {
      return RenderWindow(title, message, more_text, p_open, flags != 0 ? flags
         : KcWindowModalFlags_WarningIcon | KcWindowModalFlags_OKButton);
   }

   //-------------------------------------------------------------------------//

   KcWindowModalFlags InfoModal(const char* title, const char* message, 
      bool* p_open, const char* more_text, KcWindowModalFlags flags)
   {
      return RenderWindow(title, message, more_text, p_open, flags != 0 ? flags
         : KcWindowModalFlags_InfoIcon | KcWindowModalFlags_OKButton);
   }

   //-------------------------------------------------------------------------//
}