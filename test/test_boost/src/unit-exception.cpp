
#define BOOST_TEST_DYN_LINK

#define BOOST_TEST_MODULE "ClassTest - Config - Exception"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>

#include "../../../include/config.hpp"
#include <stdexcept>

BOOST_AUTO_TEST_CASE( config_exception_cath )
 {

    BOOST_CHECK_THROW ([&]() {
        auto config = std::make_shared<Config>("invalid_config_file.json");
    }() ,std::iostream::failure);

}
