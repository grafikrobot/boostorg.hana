/*
@copyright Louis Dionne 2014
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/functional.hpp>

#include <boost/hana/detail/static_assert.hpp>

#include <cassert>
using namespace boost::hana;


struct _extra { virtual ~_extra() { } };
_extra extra{};

#define BOOST_HANA_TEST_BINARY_OP(op, x, y)                                 \
    BOOST_HANA_STATIC_ASSERT((_ op _)(x, y) == (x op y));                   \
    assert((_ op _)(x, y, extra) == (x op y));                              \
    assert((_ op _)(x, y, extra, extra) == (x op y));                       \
                                                                            \
    BOOST_HANA_STATIC_ASSERT((_ op y)(x) == (x op y));                      \
    assert((_ op y)(x, extra) == (x op y));                                 \
    assert((_ op y)(x, extra, extra) == (x op y));                          \
                                                                            \
    BOOST_HANA_STATIC_ASSERT((x op _)(y) == (x op y));                      \
    assert((x op _)(y, extra) == (x op y));                                 \
    assert((x op _)(y, extra, extra) == (x op y));                          \
/**/

#define BOOST_HANA_TEST_UNARY_OP(op, x)                                     \
    BOOST_HANA_STATIC_ASSERT((op _)(x) == (op x));                          \
    assert((op _)(x, extra) == (op x));                                     \
    assert((op _)(x, extra, extra) == (op x));                              \
/**/

int main() {
    // Arithmetic
    BOOST_HANA_TEST_UNARY_OP(+, 1)
    BOOST_HANA_TEST_UNARY_OP(-, 1)
    BOOST_HANA_TEST_BINARY_OP(+, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(-, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(*, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(/, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(%, 6, 3)

    // Bitwise
    BOOST_HANA_TEST_UNARY_OP(~, 5)
    BOOST_HANA_TEST_BINARY_OP(&, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(|, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(^, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(<<, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(>>, 6, 3)

    // Comparison
    BOOST_HANA_TEST_BINARY_OP(==, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(!=, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(<, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(<=, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(>, 6, 3)
    BOOST_HANA_TEST_BINARY_OP(>=, 6, 3)

    // Logical
    BOOST_HANA_TEST_BINARY_OP(||, true, false)
    BOOST_HANA_TEST_BINARY_OP(&&, true, true)
    BOOST_HANA_TEST_UNARY_OP(!, true)

    // Member access
    constexpr int i = 4;
    BOOST_HANA_TEST_UNARY_OP(*, &i)
}
