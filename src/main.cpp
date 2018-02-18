#include "crow.h"
#include "spdlog/spdlog.h"

#include <iostream>
#include <memory>
#include <string>
#include <signal.h>
#include "container.hpp"

#include <boost/filesystem.hpp>

namespace spd = spdlog;
namespace fs = boost::filesystem;

void sighandler(int sig)
{
    cout<< "Signal " << sig << " caught..." << endl;
    exit(0);
}

void functionA(const std::shared_ptr<AppObject>& obj){
    obj->getRouter()->port(18080).multithreaded().run();
}

void printWorkingDir() {
    //current working directory
    fs::path path1(boost::dll::program_location());

    std::cout << path1 << std::endl;

   // std::cout << full_path.stem() << std::endl;
    //std::cout << fs::basepath(full_path) << std::endl;
}


int main()
{
    printWorkingDir();


    signal(SIGABRT, &sighandler);
    signal(SIGTERM, &sighandler);
    signal(SIGINT, &sighandler);

    auto obj = std::make_shared<AppObject>();

   // AppObject *obj = new AppObject();
    obj->logger->debug("Application started...");
    obj->setRoutes();
    
    functionA(obj);

    spd::drop_all();


    //delete obj; // release memory
    return 0;
}