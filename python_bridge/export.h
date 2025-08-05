#pragma once

#ifdef _WIN32
  #ifdef ExeLaunchHandler_PyPipeBridge_EXPORTS
    #define EXELAUNCHHANDLER_PYPIPEBRIDGE_API __declspec(dllexport)
  #else
    #define EXELAUNCHHANDLER_PYPIPEBRIDGE_API __declspec(dllimport)
  #endif
#else
  #define EXELAUNCHHANDLER_PYPIPEBRIDGE_API
#endif
