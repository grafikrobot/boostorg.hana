/*
@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#include <boost/hana/assert.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/type.hpp>

#include <type_traits>
namespace hana = boost::hana;


template <typename ...> struct f { struct type; };
struct x;
struct y;

BOOST_HANA_CONSTANT_CHECK(hana::metafunction<f>() == hana::type<f<>::type>);
BOOST_HANA_CONSTANT_CHECK(hana::metafunction<f>(hana::type<x>) == hana::type<f<x>::type>);
BOOST_HANA_CONSTANT_CHECK(hana::metafunction<f>(hana::type<x>, hana::type<y>) == hana::type<f<x, y>::type>);

// calling `metafunction` on non-Types
BOOST_HANA_CONSTANT_CHECK(hana::metafunction<f>(1) == hana::type<f<int>::type>);

static_assert(std::is_same<
    decltype(hana::metafunction<f>)::apply<x, y>::type,
    f<x, y>::type
>::value, "");

int main() { }