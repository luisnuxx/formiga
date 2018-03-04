//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "ClassTest - Config"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include <config.hpp>

BOOST_AUTO_TEST_CASE( configchecks )
{
    auto config = std::make_shared<Config>();
    auto key = config->get()["key1"];

    BOOST_CHECK( key == "value1"  );

    auto foo = config->loadFromFile();
    BOOST_CHECK(foo.length()>0);

}
