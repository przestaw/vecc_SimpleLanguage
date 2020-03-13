//
// Created by przemek on 13.03.2020.
//

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(Reader_Test_Suite)

    BOOST_AUTO_TEST_CASE(Dummy_Test) {

        BOOST_CHECK(6 == (3*2));
        BOOST_CHECK_NE(0, 1);
        BOOST_CHECK_EQUAL(17, 17);
    }


BOOST_AUTO_TEST_SUITE_END()