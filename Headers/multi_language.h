#pragma once

//----------------------------------------------------------------------------//

enum LanguageLibrary
{
   KC_LANG_EN_EN,
   KC_LANG_EN_RO
};

namespace MultiLanguage
{
   extern enum LanguageLibrary language;
}

//----------------------------------------------------------------------------//

const char* I18(const char* str);

//----------------------------------------------------------------------------//

