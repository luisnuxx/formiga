#define CATCH_CONFIG_MAIN
#include <catch.hpp>


#include <stdexcept>
#include <config.hpp>

TEST_CASE( "Config class ", "Foo test_catch2" ) {

    SECTION( "testing success" ) {
        auto config = std::make_shared<Config>();
        auto key = config->get()["key1"];
        REQUIRE( key == "value1" ); //

        auto foo = config->loadFromFile();
        REQUIRE(foo.length()>0);
    }

    SECTION( "testing error handling" ) {
        CHECK(1==1);{

            SECTION( "testing success" ) {
                auto config = std::make_shared<Config>();
                auto key = config->get()["key1"];
                REQUIRE( key == "value1" ); //

                auto foo = config->loadFromFile();
                REQUIRE(foo.length()>0);
            }

            SECTION( "testing error handling" ) {
                CHECK(1==1);
            }

        }
    }

}


TEST_CASE("Exceptions handling", "foo") {
    INFO("testing exception");

    //CHECK_THROWS_AS(config2->loadFromFile(), std::ios::failure);
    CHECK_THROWS([&]() {
        auto config2 = std::make_shared<Config>("non_existing_file.txt");
    }());

}

