#ifndef FORMIGA_ROUTES_H
#define FORMIGA_ROUTES_H
#include "crow.h"
#include <object.hpp>
#include <utils.hpp>
#include <container.hpp>

using namespace std;
class Routes {
    public:
        Routes(shared_ptr<Globals> globals);
        ~Routes();

        void create(shared_ptr<crow::SimpleApp> app);
    private:
        shared_ptr<Globals> _globals;

};


Routes::Routes(shared_ptr<Globals> globals) {
    this->_globals = globals;
    cout << "Routes constructor" << endl;
}



Routes::~Routes() {
}



void Routes::create(shared_ptr<crow::SimpleApp> app) {
    crow::mustache::set_base(".");
    CROW_ROUTE((*app), "/")([](){
        return "Hello world";
    });
   
 
    CROW_ROUTE((*app), "/json")
    ([]{
        crow::json::wvalue x;
        x["message"] = "Hello, World!";
        return x;
    });

    CROW_ROUTE((*app), "/ws")
    ([]{
        auto page = crow::mustache::load("www/ws.html");
        return page.render();
     });

    CROW_ROUTE((*app),"/hello/<int>")
    ([](int count){
        if (count > 100)
            return crow::response(400);
        std::ostringstream os;
        os << count << " bottles of beer!";
        return crow::response(os.str());
    });

    CROW_ROUTE((*app),"/js")
    ([this]{
        std::string resp = "";
        std::string script = luisnuxx::loadFileContent("./www/js/demo1.js");
        // std::cout << script << endl;
        try {
            resp = this->_globals->v8_engine->Execute(script);
        } catch (const std::exception& e) {
            std::cout << "Exception :: " <<  e.what() << std::endl;
        }
        // std::cout << " V8 :: RESPONSE :: " << resp << endl;
        // std::cout << " V8 :: EVALUATED SCRIPT :: " << script << endl;
        return crow::response(resp);
        //return crow::response("js");
    });

}


#endif //FORMIGA_ROUTES_H