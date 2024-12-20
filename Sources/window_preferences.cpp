#include "main.h"
#include "window_preferences.h"

namespace WindowPreferences
{
   void RenderWindow(bool* p_open)
   {
      // Open Window
      if (ImGui::Begin(I18("Preferences"), p_open) == false)
      {
         ImGui::End();
         return;
      }

      // display the selected language
      static int language = MultiLanguage::language;

      if (ImGui::Combo(I18("Language"), (int*)&language, "English\0Romanian\0"))
      {
         switch (language)
         {
         case (KC_LANG_EN_EN):
            MultiLanguage::language = KC_LANG_EN_EN;
            break;
         case (KC_LANG_EN_RO):
            MultiLanguage::language = KC_LANG_EN_RO;
            break;
         }
      }

      static int style_idx = -1;
      if (ImGui::Combo(I18("Theme"), &style_idx, "Keepcoding\0Dark\0Light\0Classic\0"))
      {
         switch (style_idx)
         {
         case 0: ImGui::StyleColorsKeepcoding(); break;
         case 1: ImGui::StyleColorsDark(); break;
         case 2: ImGui::StyleColorsLight(); break;
         case 3: ImGui::StyleColorsClassic(); break;
         }
      }

      // End Window
      ImGui::End();
   }
}
