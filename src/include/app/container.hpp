#include "crow.h"
#include <iostream>
#include "routes.hpp"
#include "logger.h"
using namespace std;


class AppObject
{
  private:


  public:
    AppObject();     // constructor
    crow::SimpleApp* getRouter();
    void setRoutes();
    std::shared_ptr<Logger> logger;
    ~AppObject();
 private:
    crow::SimpleApp *router;
    Routes *routes;
};

 // constructor
AppObject::AppObject()
{

    router = new crow::SimpleApp;
    routes = new Routes();

    logger = std::make_shared<Logger>();
    logger->info("foo AppObject Created");
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


void AppObject::setRoutes()
{
    //routes.create(router);
}




