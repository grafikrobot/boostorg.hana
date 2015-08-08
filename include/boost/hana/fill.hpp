/*!
@file
Defines `boost::hana::fill`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FILL_HPP
#define BOOST_HANA_FILL_HPP

#include <boost/hana/fwd/fill.hpp>

#include <boost/hana/core/datatype.hpp>
#include <boost/hana/core/default.hpp>
#include <boost/hana/core/make.hpp>
#include <boost/hana/core/models.hpp>
#include <boost/hana/core/when.hpp>
#include <boost/hana/detail/dispatch_if.hpp>
#include <boost/hana/functional/always.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/unpack.hpp>


namespace boost { namespace hana {
    struct Foldable; //! @todo include the forward declaration instead
    struct Functor;
    struct Sequence;

    //! @cond
    template <typename Xs, typename Value>
    constexpr auto fill_t::operator()(Xs&& xs, Value&& value) const {
        using S = typename datatype<Xs>::type;
        using Fill = BOOST_HANA_DISPATCH_IF(fill_impl<S>,
            _models<Functor, S>::value
        );

    #ifndef BOOST_HANA_CONFIG_DISABLE_CONCEPT_CHECKS
        static_assert(_models<Functor, S>::value,
        "hana::fill(xs, value) requires 'xs' to be a Functor");
    #endif

        return Fill::apply(static_cast<Xs&&>(xs),
                           static_cast<Value&&>(value));
    }
    //! @endcond

    template <typename Fun, bool condition>
    struct fill_impl<Fun, when<condition>> : default_ {
        template <typename Xs, typename Value>
        static constexpr auto apply(Xs&& xs, Value&& v) {
            return hana::transform(static_cast<Xs&&>(xs),
                                   hana::always(static_cast<Value&&>(v))
            );
        }
    };

    template <typename S>
    struct fill_impl<S, when<
        _models<Sequence, S>::value && _models<Foldable, S>::value
    >> {
        //! @cond
        template <typename V>
        struct filler {
            V const& v;
            template <typename ...Xs>
            constexpr auto operator()(Xs const& ...xs) const {
                return hana::make<S>(((void)xs, v)...);
            }
        };
        //! @endcond

        template <typename Xs, typename V>
        static constexpr auto apply(Xs const& xs, V const& v) {
            return hana::unpack(xs, filler<V>{v});
        }
    };
}} // end namespace boost::hana

#endif // !BOOST_HANA_FILL_HPP