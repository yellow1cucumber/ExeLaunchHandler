//
// Created by User on 05.08.2025.
//

#include "SplashScreenWrapper.h"

#include <qapplication.h>
#include <qdir.h>

namespace UI {
    SplashScreenWrapper::SplashScreenWrapper(const std::wstring &backgroundImagePath) {
        this->preparePixmap(QString::fromStdWString(backgroundImagePath));
    }

    SplashScreenWrapper::SplashScreenWrapper() {
        const QDir currentDirectory{QDir::currentPath()};
        const QString backgroundImagePath{currentDirectory.absoluteFilePath("resources/splash.png")};
        this->preparePixmap(backgroundImagePath);
    }

    SplashScreenWrapper::~SplashScreenWrapper() {
        this->hide();
    }

    void SplashScreenWrapper::preparePixmap(const QString &backgroundImagePath) {
        QPixmap pixmap{backgroundImagePath};

        if (pixmap.isNull()) {
            this->drawDefaultPixmap(pixmap);
        }

        splash = std::make_unique<QSplashScreen>(pixmap);
        splash->setWindowFlags(Qt::SplashScreen | Qt::WindowDoesNotAcceptFocus);
    }

    void SplashScreenWrapper::show() {
        this->splash->show();
        qApp->processEvents();
        if (this->afterOpen.has_value()) {
            this->afterOpen.value()();
        }
    }

    void SplashScreenWrapper::hide() {
        if (this->beforeClose.has_value()) {
            this->beforeClose.value()();
        }
        this->splash->finish(nullptr);
    }

    void SplashScreenWrapper::drawDefaultPixmap(QPixmap &pixmap) {
        pixmap = QPixmap(500, 300);
        pixmap.fill(Qt::white);

        QPainter painter(&pixmap);
        painter.setPen(Qt::black);
        painter.setFont(QFont("Arial", 20));
        painter.drawText(pixmap.rect(), Qt::AlignCenter, "Loading...");
        painter.end();
    }
} // UI
