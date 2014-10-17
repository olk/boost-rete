
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_INSTANTIATION_H
#define BOOST_RETE_INSTANTIATION_H

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <boost/rete/action.hpp>
#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class tuple;
class agenda;
class instantiation;

typedef boost::shared_ptr< tuple >			tuple_handle;
typedef boost::shared_ptr< instantiation >	instantiation_ptr;

class BOOST_RETE_DECL instantiation {
private:
	friend class agenda;

	tuple_handle 					_th;
	action_ptr						_act_ptr;
	boost::signals::connection		_con;

	instantiation( tuple_handle const&, action_ptr const&);

public:
	static instantiation_ptr create( tuple_handle const&, action_ptr const&);
	
	void operator()();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_INSTANTIATION_H
