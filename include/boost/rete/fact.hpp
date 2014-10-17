
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_FACT_H
#define BOOST_RETE_FACT_H

#include <list>
#include <typeinfo>

#include <boost/any.hpp>
#include <boost/bind.hpp>
#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <boost/rete/detail/config.hpp>
#include <boost/rete/tuple.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class fact;

template< typename T >
T & fact_cast( fact &);

class BOOST_RETE_DECL fact {
private:
	typedef boost::signal< void() >		tuple_sig_type;

	friend class tuple;
	friend class tuple::apply;
	template< typename T >
	friend T & fact_cast( fact &);

	boost::any		_any;
	tuple_sig_type	_tp_sig;
	
	void add( tuple_handle const& th) {
        _tp_sig.connect( boost::bind( & tuple::detach, th) );
    }

public:
	template< typename T >
	fact( T const& t) : 
        _any( t),
        _tp_sig()
	{}
		
	const std::type_info & type() const {
        return _any.type();
    }
	
	void remove() {
        _tp_sig();
    }
};

typedef boost::shared_ptr< fact >	fact_handle;

template< typename T >
T & fact_cast( fact & f) {
    return * boost::any_cast< T >( & f._any);
}

template< typename T >
T & fact_cast( fact_handle & fh) {
    return fact_cast< T >( * fh);
}

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_FACT_H
