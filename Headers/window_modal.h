#pragma once

// +---------------------------------------------------------------------------+
// | [SECTION] FLAGS & ENUMERATIONS                                            |
// +---------------------------------------------------------------------------+

enum KcWindowModalFlags_
{
   KcWindowModalFlags_None                                           = 0,
   KcWindowModalFlags_YesButton                                      = 1 << 0,
   KcWindowModalFlags_NoButton                                       = 1 << 1,
   KcWindowModalFlags_OKButton                                       = 1 << 3,
   KcWindowModalFlags_CancelButton                                   = 1 << 4,
   KcWindowModalFlags_ErrorIcon                                      = 1 << 5,
   KcWindowModalFlags_WarningIcon                                    = 1 << 6,
   KcWindowModalFlags_InfoIcon                                       = 1 << 7,
};

//----------------------------------------------------------------------------//

namespace WindowModal
{
   //KcWindowModalFlags RenderWindow(
   //   const char* title, 
   //   const char* message,
   //   const char* more_text,
   //   bool* p_open,
   //   KcWindowModalFlags flags = 0
   //);

   KcWindowModalFlags ErrorModal(const char* title, const char* message, 
      bool* p_open, const char* more_text = NULL, KcWindowModalFlags flags = 0);

   KcWindowModalFlags WarningModal(const char* title, const char* message, 
      bool* p_open, const char* more_text = NULL, KcWindowModalFlags flags = 0);

   KcWindowModalFlags InfoModal(const char* title, const char* message, 
      bool* p_open, const char* more_text = NULL, KcWindowModalFlags flags = 0);
}

//----------------------------------------------------------------------------//

