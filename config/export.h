#pragma once

#ifdef _WIN32
  #ifdef ExeLaunchHandler_Config_EXPORTS
    #define EXELAUNCHHANDLER_CONFIG_API __declspec(dllexport)
  #else
    #define EXELAUNCHHANDLER_CONFIG_API __declspec(dllimport)
  #endif
#else
  #define EXELAUNCHHANDLER_CONFIG_API
#endif
