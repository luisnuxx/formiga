#ifndef FORMIGA_CONTAINER_H
#define FORMIGA_CONTAINER_H
#include "crow.h"
#include <iostream>
#include <logger.h>
#include <routes.hpp>
#include <config.hpp>
#include <v8_engine.hpp>
using namespace std;

class Application
{

  public:
    Application(shared_ptr<Globals> globals);     // constructor
    shared_ptr<crow::SimpleApp> getRouter();
    void setRoutes();
    void setConfig(const shared_ptr<Config> &cfg);
    void setV8Engine(const shared_ptr<V8Engine> &v8_engine);
    shared_ptr<V8Engine> getV8Engine();
    shared_ptr<Logger> logger;

    ~Application();
  private:
    shared_ptr<crow::SimpleApp> router;
    shared_ptr<Globals> _globals;
    shared_ptr<Routes> routes;
    shared_ptr<Config> cfg;
    shared_ptr<V8Engine> v8_engine;
};

 // constructor
 Application::Application(shared_ptr<Globals> globals) {
    this->_globals = globals;
    router = make_shared<crow::SimpleApp>();
    routes = std::make_shared<Routes>(globals);
    //routes->setApplication(this);
    logger = std::make_shared<Logger>();
    logger->info("foo AppObject Created");
    routes->create(router);

    cout << "AppObject constructor called" << endl;
}

Application::~Application() // destructor, just an example
{
    //delete routes;
    //delete router;
    cout << "AppObject destructor called" << endl;
}
/*
void AppObject::setRouter(crow::SimpleApp *app)
{
  router = app;
}
*/
shared_ptr<crow::SimpleApp> Application::getRouter()
{
  return router;
}


void Application::setRoutes()
{
    //routes.create(router);
}

void Application::setConfig(const shared_ptr<Config> &cfg) {
    logger->info("Config object added to the Application");
    //std::cout << "Config object added to the Application" << std::endl;
    this->cfg = cfg;
}


void Application::setV8Engine(const shared_ptr<V8Engine> &v8_engine) {
    logger->info("V8 engine Object created and added to the application object");
    this->v8_engine = v8_engine;
}

shared_ptr<V8Engine> Application::getV8Engine() {
    return this->v8_engine;
}

#endif //FORMIGA_CONTAINER_H