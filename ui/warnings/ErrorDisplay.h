//
// Created by User on 05.08.2025.
//

#ifndef ERRORDISPLAY_H
#define ERRORDISPLAY_H
#include <string>
#include "../export.h"

namespace UI {
    class EXELAUNCHHANDLER_UI_API ErrorDisplay {
    public:
        static void showError(const std::string &summary, const std::string &message);
    };
}

#endif //ERRORDISPLAY_H
