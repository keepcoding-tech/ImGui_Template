#pragma once

#include "multi_language.h"

#include "font_awesome.h"

#include "imgui.h"
#include "imgui_internal.h"

////////////////////////////////////////////////////////////////////////////////

#define KC_VERSION     "1.1.0"
#define KC_VERSION_BN  3

////////////////////////////////////////////////////////////////////////////////

// +---------------------------------------------------------------------------+
// | [SECTION] PUBLIC GLOBAL FUNCTIONS                                         |
// +---------------------------------------------------------------------------+

void Main_CloseApplication();
void Main_ToggleFullscreen();

////////////////////////////////////////////////////////////////////////////////

// +---------------------------------------------------------------------------+
// | [SECTION] FLAGS & ENUMERATIONS                                            |
// +---------------------------------------------------------------------------+

// Flags declared as (typedef) int to allow using as flags 
// without overhead, and to not pollute the top of this file

typedef int KcWindowModalFlags;   // -> enum KcWindowModalFlags_   // Flags: for WindowModal::RenderWindow()

////////////////////////////////////////////////////////////////////////////////

// +---------------------------------------------------------------------------+
// | [SECTION] PUBLIC GLOBAL STATE                                             |
// +---------------------------------------------------------------------------+

extern bool Main_ShowExitModal;

////////////////////////////////////////////////////////////////////////////////

