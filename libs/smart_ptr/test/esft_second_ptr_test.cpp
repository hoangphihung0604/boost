//
//  esft_second_ptr_test.cpp
//
//  This test has been extracted from a real
//  scenario that occurs in Boost.Python
//
//  Copyright 2009 Peter Dimov
//
//  Distributed under the Boost Software License, Version 1.0.
//  See accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt
//


#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/detail/lightweight_test.hpp>
#include "IwTest.h"

#undef BOOST_STATIC_ASSERT
#define BOOST_STATIC_ASSERT

#undef BOOST_TEST
#define BOOST_TEST(COND) IW_TEST_ASSERT_ACTION(COND, 1 == 1, (""))

#undef BOOST_CHECK
#define BOOST_CHECK(COND) BOOST_TEST(COND)

#undef BOOST_ERROR
#define BOOST_ERROR(MSG) IwTestError(MSG)

#undef BOOST_TEST_EQ
#define BOOST_TEST_EQ(VAL1, VAL2) IW_TEST_ASSERT_EQ(VAL1, VAL2)

#undef BOOST_TEST_NE
#define BOOST_TEST_NE(VAL1, VAL2) IW_TEST_ASSERT_NOTEQ(VAL1, VAL2)

#undef BOOST_CHECK_EQUAL
#define BOOST_CHECK_EQUAL(VAL1, VAL2) IW_TEST_ASSERT_COMPARATION_IMPL(VAL1, == , VAL2, 1==1)

#undef BOOST_CHECK_THROW
#define BOOST_CHECK_THROW(S, E)                                                  \
    try {                                                                        \
        S;                                                                       \
        BOOST_ERROR("Exception was expected but not thrown - " #S);              \
    }                                                                            \
    catch( E const& ex ) {                                                       \
        ::boost::unit_test::ut_detail::ignore_unused_variable_warning( ex );     \
    }

#undef BOOST_CHECK_CLOSE_FRACTION
#define BOOST_CHECK_CLOSE_FRACTION( L, R, T )             \
    BOOST_CHECK(::boost::test_tools::check_is_close(L, R, \
        ::boost::test_tools::fraction_tolerance(T)))


/*<boost.py:auto_insert>*/ namespace esft_second_ptr_test_ns {/*<boost.py:auto_insert>*/


//

class X: public boost::enable_shared_from_this<X>
{
};

void null_deleter( void const* )
{
}

int main()
{
    boost::shared_ptr<X> px( new X );

    {
        boost::shared_ptr<X> px2( px.get(), null_deleter );
        BOOST_TEST( px == px2 );
    }

    try
    {
        boost::shared_ptr< X > qx = px->shared_from_this();

        BOOST_TEST( px == qx );
        BOOST_TEST( !( px < qx ) && !( qx < px ) );
    }
    catch( boost::bad_weak_ptr const& )
    {
        BOOST_ERROR( "px->shared_from_this() failed" );
    }

    return boost::report_errors();
}

/*<boost.py:auto_insert>*/}/*<boost.py:auto_insert>*/

IW_TEST(esft_second_ptr_test)
{
    esft_second_ptr_test_ns::main();
    return S3E_TRUE;
}
