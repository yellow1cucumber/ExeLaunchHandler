//
// Created by User on 05.08.2025.
//

#ifndef PROCESSLAUNCHER_H
#define PROCESSLAUNCHER_H
#include <export.h>

#include "AppConfig.h"

namespace Launch {
    class EXELAUNCHHANDLER_LAUNCH_API ProcessLauncher {
    public:
        bool launchDetached(Configuration::ExeRunnerConfig &config);
    };
} // Launch

#endif //PROCESSLAUNCHER_H
