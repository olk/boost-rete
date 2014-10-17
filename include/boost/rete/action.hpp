
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_ACTION_H
#define BOOST_RETE_ACTION_H

#include <functional>

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class tuple;

typedef boost::shared_ptr< tuple >		tuple_handle;

class BOOST_RETE_DECL action : public std::unary_function< tuple_handle &, void > {
public:
    virtual ~action() {}		
    virtual void operator()( tuple_handle &) = 0;		
    virtual long priority() const = 0;
};

typedef boost::shared_ptr< action >		action_ptr;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_ACTION_H
