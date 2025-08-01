//
// Created by User on 01.08.2025.
//

#include "ConfigManager.h"

namespace Configuration {
    void ConfigManager::init(std::unique_ptr<Converting::ISerializer> serializer,
                             const std::string &configFilePath) {
        std::call_once(initFlag, [&]() {
            instance.reset(new ConfigManager(std::move(serializer), configFilePath));
        });
    }

    ConfigManager &ConfigManager::getInstance() {
        if (!instance) {
            throw std::runtime_error("ConfigManager::getInstance() called with null instance");
        }
        return *instance;
    }

    const AppConfig &ConfigManager::loadFromFile(const std::string &filePath) {
        std::lock_guard lock(writeMutex);
        this->config = this->serializer->fromFile(filePath);
        return this->config.value();
    }

    const AppConfig & ConfigManager::loadFromFile() {
        return this->loadFromFile(this->configFilePath);
    }

    void ConfigManager::save(const std::optional<std::string> &filePath, const std::optional<AppConfig> &config) {
        const AppConfig &cfg{config.value_or(this->config.value())};
        const std::string &path{filePath.value_or(this->configFilePath)};
        std::lock_guard lock(writeMutex);
        this->serializer->toFile(path, cfg);

        this->config = cfg; // Update the cached config
    }

    const std::optional<AppConfig> &ConfigManager::getCached() const {
        return this->config;
    }

    ConfigManager::ConfigManager(std::unique_ptr<Converting::ISerializer> serializer,
                                 const std::string &configFilePath)
        : serializer(std::move(serializer)), configFilePath(configFilePath) {
    }
}
