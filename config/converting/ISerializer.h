//
// Created by User on 28.07.2025.
//

#ifndef ISERIALIZER_H
#define ISERIALIZER_H
#include <string>

#include "../AppConfig.h"
#include "../export.h"

namespace Configuration::Converting {
    class EXELAUNCHHANDLER_CONFIG_API ISerializer {
    public:
        virtual const Configuration::AppConfig fromFile(const std::string &filePath) = 0;
        virtual void toFile(const std::string& filePath, const AppConfig& config) = 0;

        virtual ~ISerializer() = default;
    };
}

#endif //ISERIALIZER_H
