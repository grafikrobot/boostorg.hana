/*!
@file
Forward declares `boost::hana::append`.

@copyright Louis Dionne 2015
Distributed under the Boost Software License, Version 1.0.
(See accompanying file LICENSE.md or copy at http://boost.org/LICENSE_1_0.txt)
 */

#ifndef BOOST_HANA_FWD_APPEND_HPP
#define BOOST_HANA_FWD_APPEND_HPP

#include <boost/hana/core/when.hpp>


namespace boost { namespace hana {
    //! Append an element to a monadic structure.
    //! @relates MonadPlus
    //!
    //! Given an element `x` of data type `X` and a monadic structure
    //! `xs` containing objects of data type `X`, `append` returns a
    //! new monadic structure which is the result of lifting `x` into
    //! the monadic structure and then combining that (to the right)
    //! with `xs`. In other words,
    //! @code
    //!     append(xs, x) == concat(xs, lift<Xs>(x))
    //! @endcode
    //!
    //! For sequences, this has the intuitive behavior of simply appending
    //! an element to the end of the sequence, hence the name.
    //!
    //! > #### Rationale for not calling this `push_back`
    //! > See the rationale for using `prepend` instead of `push_front`.
    //!
    //!
    //! Signature
    //! ---------
    //! Given a MonadPlus `M`, the signature is
    //! @f$ \mathtt{append} : M(T) \times T \to M(T) @f$.
    //!
    //! @param xs
    //! A monadic structure that will be combined to the left of the element.
    //!
    //! @param x
    //! An element to combine to the right of the monadic structure.
    //!
    //!
    //! Example
    //! -------
    //! @snippet example/monad_plus.cpp append
#ifdef BOOST_HANA_DOXYGEN_INVOKED
    constexpr auto append = [](auto&& xs, auto&& x) {
        return tag-dispatched;
    };
#else
    template <typename M, typename = void>
    struct append_impl : append_impl<M, when<true>> { };

    struct append_t {
        template <typename Xs, typename X>
        constexpr auto operator()(Xs&& xs, X&& x) const;
    };

    constexpr append_t append{};
#endif
}} // end namespace boost::hana

#endif // !BOOST_HANA_FWD_APPEND_HPP