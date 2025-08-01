#pragma once

#ifdef _WIN32
  #ifdef ExeLaunchHandler_UI_EXPORTS
    #define EXELAUNCHHANDLER_UI_API __declspec(dllexport)
  #else
    #define EXELAUNCHHANDLER_UI_API __declspec(dllimport)
  #endif
#else
  #define EXELAUNCHHANDLER_UI_API
#endif
