#include "crow.h"
#include <iostream>
#include "routes.hpp"
#include "logger.h"
#include <config.hpp>
using namespace std;


class Application
{

  public:
    Application();     // constructor
    crow::SimpleApp* getRouter();
    void setRoutes();
    void setConfig(const shared_ptr<Config> &cfg);
    std::shared_ptr<Logger> logger;
    ~Application();
  private:
    crow::SimpleApp *router;
    Routes *routes;
    shared_ptr<Config> cfg;
};

 // constructor
 Application::Application()
{

    router = new crow::SimpleApp;
    routes = new Routes();

    logger = std::make_shared<Logger>();
    logger->info("foo AppObject Created");
    routes->create(router);

    cout << "AppObject constructor called" << endl;
}

Application::~Application() // destructor, just an example
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
crow::SimpleApp* Application::getRouter()
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




