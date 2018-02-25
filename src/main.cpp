#include "crow.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <memory>
#include <string>
#include <signal.h>
#include "container.hpp"
#include <utils.hpp>
#include <config.hpp>

namespace spd = spdlog;

void sighandler(int sig)
{
    cout<< "Signal " << sig << " caught..." << endl;
    exit(0);
}

void run(const std::shared_ptr<Application>& obj){
    obj->getRouter()->port(18080).multithreaded().run();
}


int main()
{
    std::cout << "Working directory:: " << luisnuxx::getWorkingDir() << endl;

    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGINT, &sighandler);

    auto config = std::make_shared<Config>();
    std::cout << config->get()["key1"] << std::endl;

    auto obj = std::make_shared<Application>();

   // AppObject *obj = new AppObject(); (old)
    obj->logger->debug("Application started...");
    obj->setRoutes();
    obj->setConfig(config);

    run(obj);

    std::cout << "Exiting main" << endl;
    //delete obj; // release memory (old)
    return 0;
}