//
// Created by User on 05.08.2025.
//

#ifndef SPLASHSCREENWRAPPER_H
#define SPLASHSCREENWRAPPER_H

#include <functional>
#include <memory>
#include <optional>
#include <string>

#include <QSplashScreen>
#include <QPainter>

#include "../export.h"

namespace UI {

class EXELAUNCHHANDLER_UI_API SplashScreenWrapper {
public:
    explicit SplashScreenWrapper(const std::wstring& backgroundImagePath);
    explicit SplashScreenWrapper();
    ~SplashScreenWrapper();

    void show();
    void hide();

    std::optional<std::function<void()>> afterOpen;
    std::optional<std::function<void()>> beforeClose;

private:
    std::unique_ptr<QSplashScreen> splash;

    void preparePixmap(const QString &backgroundImagePath);

    void drawDefaultPixmap(QPixmap &pixmap);
};

} // UI

#endif //SPLASHSCREENWRAPPER_H
