#pragma once

#include "main.h"

namespace WindowMain
{
   struct WindowMainData
   {
      // +---------------------------------------------------------------------+
      // | [SECTION] Menu Bar Flags                                            |
      // +---------------------------------------------------------------------+

      // MenuBar -> File
      bool OpenPreferences = false;

      // MenuBar -> View
      bool ShowToolBar  = true;
      bool ShowSideBar  = true;
      bool ShowDebugLog = false;
#ifdef _DEBUG
      bool ShowDemoWindow = false;
#endif

      // MenuBar -> Help
      bool ShowChangeLogWindow = false;
      bool ShowAboutWindow     = false;

      // +---------------------------------------------------------------------+
      // | [SECTION] Warning & Error Flags                                     |
      // +---------------------------------------------------------------------+

      // TODO: make an Init() function that takes the values from a config file
      ~WindowMainData() {}
   };

   void RenderMainWindow();
}