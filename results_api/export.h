#pragma once

#ifdef _WIN32
  #ifdef ExeLaunchHandler_ResultsAPI_EXPORTS
    #define EXELAUNCHHANDLER_RESULTSAPI_API __declspec(dllexport)
  #else
    #define EXELAUNCHHANDLER_RESULTSAPI_API __declspec(dllimport)
  #endif
#else
  #define EXELAUNCHHANDLER_RESULTSAPI_API
#endif
