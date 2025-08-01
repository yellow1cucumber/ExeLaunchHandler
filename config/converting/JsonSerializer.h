//
// Created by User on 28.07.2025.
//

#ifndef JSONSERIALIZER_H
#define JSONSERIALIZER_H
#include "ISerializer.h"
#include "json.hpp"

#include "../export.h"

namespace Configuration::Converting {
    class EXELAUNCHHANDLER_CONFIG_API JsonSerializer final: public ISerializer {
    public:
        const Configuration::AppConfig fromFile(const std::string &filePath) override;

        void toFile(const std::string &filePath, const AppConfig& config) override;

    private:
        static void fromJson(const nlohmann::json &json, AppConfig &config);
        static nlohmann::json toJson(const AppConfig &config);

        static void fromJson(const nlohmann::json &json, LoggerConfig &config);
        static void fromJson(const nlohmann::json &json, PipesConfig &config);
        static void fromJson(const nlohmann::json &json, ExeRunnerConfig &config);

        static nlohmann::json toJson(const LoggerConfig &config);
        static nlohmann::json toJson(const PipesConfig &config);
        static nlohmann::json toJson(const ExeRunnerConfig &config);
    };
}


#endif //JSONSERIALIZER_H
