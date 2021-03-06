#include "Logging.h"
#include "config/nheko.h"

#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"
#include <iostream>

namespace {
std::shared_ptr<spdlog::logger> db_logger     = nullptr;
std::shared_ptr<spdlog::logger> net_logger    = nullptr;
std::shared_ptr<spdlog::logger> crypto_logger = nullptr;
std::shared_ptr<spdlog::logger> ui_logger     = nullptr;

constexpr auto MAX_FILE_SIZE = 1024 * 1024 * 6;
constexpr auto MAX_LOG_FILES = 3;
}

namespace nhlog {
void
init(const std::string &file_path)
{
        auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
          file_path, MAX_FILE_SIZE, MAX_LOG_FILES);

        auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();

        std::vector<spdlog::sink_ptr> sinks;
        sinks.push_back(file_sink);
        sinks.push_back(console_sink);

        net_logger = std::make_shared<spdlog::logger>("net", std::begin(sinks), std::end(sinks));
        ui_logger  = std::make_shared<spdlog::logger>("ui", std::begin(sinks), std::end(sinks));
        db_logger  = std::make_shared<spdlog::logger>("db", std::begin(sinks), std::end(sinks));
        crypto_logger =
          std::make_shared<spdlog::logger>("crypto", std::begin(sinks), std::end(sinks));

        if (nheko::enable_debug_log) {
                db_logger->set_level(spdlog::level::trace);
                ui_logger->set_level(spdlog::level::trace);
                crypto_logger->set_level(spdlog::level::trace);
        }
}

std::shared_ptr<spdlog::logger>
ui()
{
        return ui_logger;
}

std::shared_ptr<spdlog::logger>
net()
{
        return net_logger;
}

std::shared_ptr<spdlog::logger>
db()
{
        return db_logger;
}

std::shared_ptr<spdlog::logger>
crypto()
{
        return crypto_logger;
}
}
