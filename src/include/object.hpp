#include "crow.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <memory>
#include <string>

namespace spd = spdlog;

struct AppObject {
    crow::SimpleApp *router;
    std::shared_ptr<spdlog::logger> logger;
    std::string message;
};


