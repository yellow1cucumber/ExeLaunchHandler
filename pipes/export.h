#pragma once

#ifdef _WIN32
  #ifdef ExeLaunchHandler_Pipes_EXPORTS
    #define EXELAUNCHHANDLER_PIPES_API __declspec(dllexport)
  #else
    #define EXELAUNCHHANDLER_PIPES_API __declspec(dllimport)
  #endif
#else
  #define EXELAUNCHHANDLER_PIPES_API
#endif
