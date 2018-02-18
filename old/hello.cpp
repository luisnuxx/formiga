#include "crow.h"
#include "spdlog/spdlog.h"
#include "object.hpp"
#include <iostream>
#include <memory>
#include <string>

namespace spd = spdlog;






auto configureLog() {
    // Create a file rotating logger with 5mb size max and 3 rotated files
    auto rotating_logger = spd::rotating_logger_mt("rotate_logger", "logs/mylogfile", 1048576 * 5, 3);
    
    rotating_logger->set_level(spd::level::debug); // Set specific logger's log level
    

    spd::set_pattern("*** [%H:%M:%S %z] [thread %t] %v ***");
    return rotating_logger;
}

/*
void debug(auto &logger,std::string message) {
 try
    {
       

logger->debug("{}",message);
       
       
    } catch (const spd::spdlog_ex& ex)
    {
        std::cout << "Log init failed: " << ex.what() << std::endl;
        return 1;
    }
}
*/
void printA(AppObject &myApp) {
    std::cout << "MyApp.message: " << myApp.message << std::endl;
    myApp.logger->debug("logger::debug:: {} ",myApp.message);
}

void defineRoutes(AppObject &myApp) {
    crow::SimpleApp app =  *myApp.router; // copy the router
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    CROW_ROUTE(app, "/json")
    ([]{
        crow::json::wvalue x;
        x["message"] = "Hello, World!";
        return x;
    });

    CROW_ROUTE(app,"/hello/<int>")
    ([](int count){
        if (count > 100)
            return crow::response(400);
        std::ostringstream os;
        os << count << " bottles of beer!";
        return crow::response(os.str());
    });
}



int main()
{
    crow::SimpleApp app;
    CROW_ROUTE(app, "/")([](){
        return "Hello world";
    });

    AppObject obj;
    obj.logger = configureLog();
    obj.router = &app;
    obj.message = "blahh";

    defineRoutes(obj);

    printA(obj);
    
    //defineRoutes(app,logger);
    app.port(18080).multithreaded().run();

    spd::drop_all();

}