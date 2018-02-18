#include "crow.h"
#include "spdlog/spdlog.h"
#include <iostream>      // for cout and cin
#include "routes.hpp"
using namespace std;
namespace spd = spdlog;

class AppObject                   // begin declaration of the class
{
  public:                    // begin public section
    AppObject();     // constructor
   
    ~AppObject();                  // destructor

    //static auto getLogger();            // accessor function
    //void setLogger[](auto logger);    // accessor function
    void printA();
    //void setRouter(crow::SimpleApp *app); // set the router app
    crow::SimpleApp* getRouter();
    void initLogger();
    void setRoutes();
    std::shared_ptr<spd::logger> logger;

 private:                   // begin private section
    //auto logger;              // member variable
    crow::SimpleApp *router;
    Routes *routes;
};

 // constructor 
AppObject::AppObject()
{
    router = new crow::SimpleApp;
    routes = new Routes();
    
    initLogger();
    routes->create(router);
    cout << "AppObject constructor called" << endl;
}

AppObject::~AppObject() // destructor, just an example
{
    delete routes;
    delete router;
    cout << "AppObject destructor called" << endl;
}
/*
void AppObject::setRouter(crow::SimpleApp *app)
{
  router = app;
}
*/
crow::SimpleApp* AppObject::getRouter()
{
  return router;
}

 
 
void AppObject::initLogger() {
     // Create a file rotating logger with 5mb size max and 3 rotated files
    logger = spd::rotating_logger_mt("rotate_logger", "log/formiga.log", 1048576 * 5, 3);
    logger->set_level(spd::level::err); // Set specific logger's log level
    spd::set_pattern("*** [%H:%M:%S %z] [thread %t] %v ***");
}

void AppObject::printA()
{
   cout << "AAAAA.\n" << endl;
}

void AppObject::setRoutes()
{
    //routes.create(router);
}




