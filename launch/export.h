#pragma once

#ifdef _WIN32
  #ifdef ExeLaunchHandler_Launch_EXPORTS
    #define EXELAUNCHHANDLER_LAUNCH_API __declspec(dllexport)
  #else
    #define EXELAUNCHHANDLER_LAUNCH_API __declspec(dllimport)
  #endif
#else
  #define EXELAUNCHHANDLER_LAUNCH_API
#endif
