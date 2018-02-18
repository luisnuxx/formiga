//
// Created by Luis Rodrigues on 18/02/2018.
//

#include "logger.h"
namespace spd = spdlog;

Logger::Logger() {
    // Create a file rotating logger with 5mb size max and 3 rotated files
    logger = spd::rotating_logger_mt("rotate_logger", "log/formiga.log", 1048576 * 5, 3);
    logger->set_level(spd::level::debug); // Set specific logger's log level
    spd::set_pattern("%+");  //https://github.com/gabime/spdlog/wiki/3.-Custom-formatting
    logger->flush_on(spd::level::err); //trigger flush if the log severity is error or higher
}

void Logger::debug(std::string txt) {
    logger->debug(txt);
}

void Logger::info(std::string txt) {
    logger->info(txt);
}

void Logger::error(std::string txt) {
    logger->error(txt);
}

void Logger::critical(std::string txt) {
    logger->critical(txt);
}

std::shared_ptr<spd::logger>& Logger::getLogger(std::string txt) {
    return logger;
}

Logger::~Logger() {
    // Release and close all loggers
    logger->info("Logger:: Destructor called ... calling [drop_all]");
    spd::drop_all();
}


