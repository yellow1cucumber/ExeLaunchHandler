//
// Created by User on 01.08.2025.
//

#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <export.h>
#include <memory>
#include <mutex>

#include "converting/ISerializer.h"

namespace Configuration {
    class EXELAUNCHHANDLER_CONFIG_API ConfigManager {
    public:
        static void init(std::unique_ptr<Converting::ISerializer> serializer, const std::string &configFilePath);

        static ConfigManager &getInstance();

        const AppConfig &loadFromFile(const std::string &filePath);
        const AppConfig &loadFromFile();

        void save(const std::optional<std::string> &filePath, const std::optional<AppConfig> &config);

        const std::optional<AppConfig>& getCached() const;

    private:
        ConfigManager(std::unique_ptr<Converting::ISerializer> serializer, const std::string &configFilePath);

        inline static std::once_flag initFlag;
        inline static std::unique_ptr<ConfigManager> instance;

        std::unique_ptr<Converting::ISerializer> serializer;

        std::optional<AppConfig> config;
        const std::string configFilePath;
        std::mutex writeMutex;
    };
}
#endif //CONFIGMANAGER_H
