#include "utils/Logs.h"
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <sstream>
#include <filesystem>
#include <chrono>

Logs& Logs::instance() {
    static Logs instance;
    return instance;
}

Logs::Logs() 
{
    init();
}

Logs::~Logs()
{
   // spdlog::drop_all();
}

void Logs::init() 
{
    // Get the current date and time
    auto now = std::chrono::system_clock::now();
    auto now_c = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm = *std::localtime(&now_c);
    std::stringstream ss;
    ss << std::put_time(&now_tm, "%Y%m%d_%H%M%S");

    // Count the number of existing log files
    int fileCount = 0;
    std::string logDir = "saved/logs/";
    for (const auto& entry : std::filesystem::directory_iterator(logDir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".txt") {
            fileCount++;
        }
    }
    log_file_name = logDir + "Shatterpoint_Log_" + std::to_string(fileCount + 1) + "_" + ss.str() + ".txt";
}

std::shared_ptr<spdlog::logger> Logs::createLogger(const std::string& name) 
{
    auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(log_file_name, 1048576 * 5, 3);
    auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

    std::vector<spdlog::sink_ptr> sinks {file_sink, console_sink};
    auto logger = std::make_shared<spdlog::logger>(name, begin(sinks), end(sinks));
    logger->set_level(spdlog::level::info);

    logger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [" + name + "] [%^%l%$] %v");
    return logger;
}
