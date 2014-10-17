
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_DETAIL_CONFIG_H
#define BOOST_RETE_DETAIL_CONFIG_H

#include <boost/config.hpp>
#include <boost/detail/workaround.hpp>

#ifdef BOOST_RETE_DECL
# undef BOOST_RETE_DECL
#endif

#if (defined(BOOST_ALL_DYN_LINK) || defined(BOOST_RETE_DYN_LINK) ) && ! defined(BOOST_RETE_STATIC_LINK)
# if defined(BOOST_RETE_SOURCE)
#  define BOOST_RETE_DECL BOOST_SYMBOL_EXPORT
#  define BOOST_RETE_BUILD_DLL
# else
#  define BOOST_RETE_DECL BOOST_SYMBOL_IMPORT
# endif
#endif

#if ! defined(BOOST_RETE_DECL)
# define BOOST_RETE_DECL
#endif

#if ! defined(BOOST_RETE_SOURCE) && ! defined(BOOST_ALL_NO_LIB) && ! defined(BOOST_RETE_NO_LIB)
# define BOOST_LIB_NAME boost_coroutine
# if defined(BOOST_ALL_DYN_LINK) || defined(BOOST_RETE_DYN_LINK)
#  define BOOST_DYN_LINK
# endif
# include <boost/config/auto_link.hpp>
#endif

#endif // BOOST_RETE_DETAIL_CONFIG_H
