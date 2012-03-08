#pragma once


//----------------------------------------------------------------------------------
//	Include
//----------------------------------------------------------------------------------

#include <boost/test/unit_test.hpp>
#include "Util/Common.h"


//----------------------------------------------------------------------------------
//	Define
//----------------------------------------------------------------------------------

#define TestSuite( name ) BOOST_AUTO_TEST_SUITE( name )
#define TestSuiteEnd() BOOST_AUTO_TEST_SUITE_END()

#define TestCase( name ) BOOST_AUTO_TEST_CASE( name )

#define Check( expression ) BOOST_CHECK( expression )
#define CheckEqual( expected, actual ) BOOST_CHECK_EQUAL( expected, actual )
#define CheckEqualCollection( L_begin, L_end, R_begin, R_end ) BOOST_CHECK_EQUAL_COLLECTIONS( L_begin, L_end, R_begin, R_end )
#define CheckThrow( statement, exception ) BOOST_CHECK_THROW( statement, exception )
#define Fail( message ) BOOST_FAIL( message )