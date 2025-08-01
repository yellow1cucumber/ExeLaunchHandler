#pragma once

#ifdef _WIN32
  #ifdef ExeLaunchHandler_Logging_EXPORTS
    #define EXELAUNCHHANDLER_LOGGING_API __declspec(dllexport)
  #else
    #define EXELAUNCHHANDLER_LOGGING_API __declspec(dllimport)
  #endif
#else
  #define EXELAUNCHHANDLER_LOGGING_API
#endif
