#include "crow.h"
using namespace std;
class Routes {
public:
    Routes();
    ~Routes();
    void create(crow::SimpleApp *app);
private:

};


Routes::Routes() {
    cout << "Routes constructor" << endl;
}


Routes::~Routes() {
}


void Routes::create(crow::SimpleApp *app) {
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
     
}
