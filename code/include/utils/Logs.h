#pragma once

#include <spdlog/spdlog.h>
#include <memory>
#include <string>
#include <unordered_map>

class Logs {
public:
    static Logs& instance();

    template<typename... Args>
    void log(const std::string& category, spdlog::level::level_enum lvl, const std::string& msg, Args... args) 
    {
        std::shared_ptr<spdlog::logger> logger;
        auto it = loggers.find(category);
        if (it != loggers.end()) {
            logger = it->second;
        }
        else {
            logger = createLogger(category);
            loggers[category] = logger;
        }

        logger->log(lvl, msg, args...);
    }
private:
    Logs();
    ~Logs();
    void init();
    std::shared_ptr<spdlog::logger> createLogger(const std::string& name);

    std::unordered_map<std::string, std::shared_ptr<spdlog::logger>> loggers;
    std::string log_file_name;
};

