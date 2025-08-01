#include <iostream>
#include <QApplication>
#include <QPushButton>

#include "cxxopts.hpp"
#include "config/ConfigManager.h"
#include "config/converting/JsonSerializer.h"
#include "ui/main_window/mainwindow.h"

int main(int argc, char *argv[]) {
    cxxopts::Options options{
        "ExeLaunchHandler",
        "Proxy ПО для запуска исполняемых файлов, для которых необходимо выполнить дополнительные действия перед запуском."
    };

    options.add_options()
    ("c,config", "Путь к файлу конфигурации", cxxopts::value<std::string>())
    ("h,help", "Показать справку");
    const auto result = options.parse(argc, argv);

    if (result["help"].as<bool>()) {
        std::cout << options.help();
        return 0;
    }

    const auto configPath = result["config"].as<std::string>();
    if (configPath.empty()) {
        std::cerr << "Не указан путь к файлу конфигурации." << std::endl;
        return 1;
    }

    Configuration::ConfigManager::init(std::make_unique<Configuration::Converting::JsonSerializer>(), configPath);

    try {
        const auto& config { Configuration::ConfigManager::getInstance().loadFromFile() };
    } catch (const std::runtime_error &e) {
        std::cerr << "Ошибка при загрузке конфигурации: " << e.what() << std::endl;
        return 1;
    }

    QApplication a(argc, argv);

    UI::MainWindow mainWindow;
    mainWindow.show();

    return QApplication::exec();
}
