//
// Created by Luis Rodrigues on 18/02/2018.
//

#ifndef FORMIGA_LOGGER_H
#define FORMIGA_LOGGER_H
#include "spdlog/spdlog.h"
namespace spd = spdlog;

class Logger {

    public:
        Logger();
        void debug(std::string txt);
        void info(std::string txt);
        void error(std::string txt);
        void critical(std::string txt);

        std::shared_ptr<spd::logger>& getLogger(std::string txt);

        ~Logger();
    private:

        std::shared_ptr<spd::logger> logger;
};


#endif //FORMIGA_LOGGER_H
