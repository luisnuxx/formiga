#include <first_include.hpp>
#include "crow.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <memory>
#include <string>
#include <signal.h>

#include "container.hpp"

#include <utils.hpp>
#include <config.hpp>
#include <v8_engine.hpp>
#include <exception>
#include <static_test.hpp>
#include <object.hpp>

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
    auto globals = std::make_shared<Globals>();
    std::cout << "Working directory:: " << luisnuxx::getWorkingDir() << endl;

    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGINT, &sighandler);

    auto config = std::make_shared<Config>();
    std::cout << config->get()["key1"] << std::endl;

    auto v8_engine = std::make_shared<V8Engine>();
    v8_engine->Initialize();

    globals->v8_engine = v8_engine;

    auto obj = std::make_shared<Application>(globals);

    auto staticTest = make_unique<StaticTest>();
    staticTest->setFoo(100);



   // AppObject *obj = new AppObject(); (old)
    obj->logger->debug("Application started...");
    obj->setRoutes();
    obj->setConfig(config);
    obj->setV8Engine(v8_engine);
    // Start the TCP binding
    run(obj);
    try {
        std::cout << "@1::" << v8_engine->Execute("'Hello' + ', World!'") << std::endl;
        std::cout << "@2::" << v8_engine->Execute(luisnuxx::loadFileContent("./www/js/demo1.js")) << std::endl;
    }catch(exception& e) {
        std::cout << "Exception caught :: " << e.what() << std::endl;
    }


    v8_engine->Destroy();
    std::cout << "Foo Value is :: " <<  staticTest->getFoo() << endl;
    std::cout << "Exiting main" << endl;
    //delete obj; // release memory (old)
    return 0;
}