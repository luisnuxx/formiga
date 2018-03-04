//Link to Boost
#define BOOST_TEST_DYN_LINK

//Define our Module name (prints at testing)
#define BOOST_TEST_MODULE "Dummy assert"

//VERY IMPORTANT - include this last
#include <boost/test/unit_test.hpp>



BOOST_AUTO_TEST_CASE( DUMMY_TRUE )
{
    BOOST_CHECK( 1 == 1 );

}
