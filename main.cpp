#include "app.h"
#include "global_error_handler.h"

#include "cxxopts.hpp"
#include "ui/splash_screen/SplashScreenWrapper.h"
#include "ui/warnings/ErrorDisplay.h"


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    ErrorHandler::installGlobalHandlers();

    if (App::shouldShowHelp(argc, argv)) {
        App::printHelp();
        return 0;
    }

    const auto configPath = App::getConfigPath(argc, argv);
    const bool uiMode = App::isUIModeEnabled(argc, argv);

    std::unique_ptr<UI::SplashScreenWrapper> splashScreen;
    if (!uiMode) {
        splashScreen = std::make_unique<UI::SplashScreenWrapper>();
        splashScreen->show();

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    bool pipelineOk = false;
    std::optional<Configuration::AppConfig> appConfig;

    try {
        appConfig = App::initApplication(configPath);

        if (uiMode) {
            return App::runUIMode();
        }

        pipelineOk = App::runPipeline(configPath);
    } catch (const std::exception &e) {
        UI::ErrorDisplay::showError("Ошибка при инициализации", e.what());
    } catch (...) {
        UI::ErrorDisplay::showError("Неизвестная ошибка", "Произошла неизвестная ошибка при запуске");
    }

    bool launchOk = false;

    try {
        if (appConfig.has_value()) {
            launchOk = App::launchProcess(*appConfig);
        }
    } catch (const std::exception &e) {
        UI::ErrorDisplay::showError("Ошибка запуска процесса", e.what());
    } catch (...) {
        UI::ErrorDisplay::showError("Неизвестная ошибка", "Произошла ошибка при запуске процесса");
    }

    if (!launchOk) {
        UI::ErrorDisplay::showError("Не удалось запустить процесс",
                                    "Запустите приложение вручную, дайте сисадмину банку редбула и заставьте его починить это");
    }

    if (splashScreen) splashScreen->hide();

    return pipelineOk && launchOk ? 0 : 1;
}
