#ifndef FORMIGA_OBJECT_H
#define FORMIGA_OBJECT_H
#include "crow.h"
#include "spdlog/logger.h"
#include "spdlog/spdlog.h"
#include <iostream>
#include <memory>
#include <string>
#include <v8_engine.hpp>

using namespace std;
namespace spd = spdlog;

struct Globals {
    public:
        Globals() { std::cout << "c'tor" << std::endl; }
        ~Globals() { std::cout << "d'tor" << std::endl; }
        shared_ptr<crow::SimpleApp> router;
        shared_ptr<spdlog::logger> logger;
        string message;
        shared_ptr<V8Engine> v8_engine;
};

#endif

