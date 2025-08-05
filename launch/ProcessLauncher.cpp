//
// Created by User on 05.08.2025.
//

#include "ProcessLauncher.h"

#include <sstream>

namespace Launch {
    bool ProcessLauncher::launchDetached(const Configuration::ExeRunnerConfig &config) const {
        const std::wstring exePath{config.exePath.begin(), config.exePath.end()};
        std::wstring args;

        if (!config.exeArgs->empty()) {
            args = std::wstring(config.exeArgs->begin(), config.exeArgs->end());
        }

        std::wstring commandLine{L"\"" + exePath + L"\" " + args};

        STARTUPINFOW si = {sizeof(si)};
        PROCESS_INFORMATION pi;

        const DWORD dwCreationFlags{Constants::Processes::toWindowsPRIORITY(config.processPriority.value())};

        const BOOL result = CreateProcessW(
            nullptr, // lpApplicationName
            &commandLine[0], // lpCommandLine (modifiable buffer!)
            nullptr, // lpProcessAttributes
            nullptr, // lpThreadAttributes
            FALSE, // bInheritHandles
            dwCreationFlags, // dwCreationFlags
            nullptr, // lpEnvironment
            nullptr, // lpCurrentDirectory
            &si, // lpStartupInfo
            &pi // lpProcessInformation
        );

        if (result) {
            CloseHandle(pi.hProcess);
            CloseHandle(pi.hThread);
        }

        return result == TRUE;
    }

} // Launch
