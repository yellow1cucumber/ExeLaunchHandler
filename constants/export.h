#pragma once

#ifdef _WIN32
  #ifdef ExeLaunchHandler_Constants_EXPORTS
    #define EXELAUNCHHANDLER_CONSTANTS_API __declspec(dllexport)
  #else
    #define EXELAUNCHHANDLER_CONSTANTS_API __declspec(dllimport)
  #endif
#else
  #define EXELAUNCHHANDLER_CONSTANTS_API
#endif
