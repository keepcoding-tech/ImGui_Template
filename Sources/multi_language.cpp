#include "multi_language.h"

#include <unordered_map>

//----------------------------------------------------------------------------//

namespace MultiLanguage
{
   enum LanguageLibrary language = KC_LANG_EN_EN;
}

//----------------------------------------------------------------------------//

std::unordered_map<const char*, const char*> lang_en_ro =
{
   { "About",                                                                    "Despre" },
   { "Are you sure you want to exit the application?",                           "Sunteti sigur ca doriti sa parasiti aplicatia?" },
   { "By keepcoding.tech with the help of Dear ImGui.",                          "De keepcoding.tech cu ajutorul Dear ImGui."},
   { "Cancel",                                                                   "Renunta" },
   { "Change Log",                                                               "Jurnal de Modificari" },
   { "Config/Build Information",                                                 "Informatii de configurare" },
   { "Console",                                                                  "Pupitru de Comanda" },
   { "Copy to clipboard",                                                        "Copiati in clipboard" },
   { "Documentation",                                                            "Documentatie" },
   { "Debug Log",                                                                "Jurnal de Depanare" },
   { "Exit",                                                                     "Iesire" },
   { "Exit Application",                                                         "Iesiti din aplicatie" },
   { "File",                                                                     "Fisier" },
   { "Full Screen",                                                              "Ecran Complet" },
   { "Help",                                                                     "Ajutor"},
   { "Homepage",                                                                 "Acasa"},
   { "If your are using this, please consider funding the project.",             "Daca o utilizati, va rog sa luati in considerare finantarea proiectului." },
   { "Language",                                                                 "Limbaj" },
   { "Less",                                                                     "Mai putin" },
   { "LICENSE",                                                                  "LICENTA"},
   { "Log In",                                                                   "Autentificare" },
   { "Log Out",                                                                  "Deconectare" },
   { "Menu",                                                                     "Meniu"},
   { "More",                                                                     "Mai mult" },
   { "No",                                                                       "Nu" },
   { "OK",                                                                       "OK" },
   { "Preferences",                                                              "Preferinte" },
   { "promoting freedom and collaboration among developers.",                    "promovand libertatea si colaborarea dintre dezvoltatori." },
   { "See LICENSE for more information.",                                        "Consultati LICENTA pentru mai multe informatii." },
   { "Settings",                                                                 "Setari" },
   { "Side Bar",                                                                 "Bara Laterala" },
   { "Theme",                                                                    "Tema" },
   { "This application is open - source and distributed under the MIT license,", "Aceasta aplicatie este open source si distribuita sub licenta MIT," },
   { "Tool Bar",                                                                 "Bara de Unelte" },
   { "View",                                                                     "Vizualizare"},
   { "Welcome",                                                                  "Bun Venit!" },
   { "Yes",                                                                      "Da" },
};

//----------------------------------------------------------------------------//

const char* I18(const char* str)
{
   switch (MultiLanguage::language)
   {
      case KC_LANG_EN_EN:
      {
         return str;
      }

      case KC_LANG_EN_RO:
      {
         // check translation existance
         if (lang_en_ro.count(str))
         {
            return lang_en_ro[str];
         }

         // return same string 
         // if does not exists
         return str;
      }
   }

   return str;
}

//----------------------------------------------------------------------------//
