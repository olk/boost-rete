
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/agenda.hpp"

#include <boost/bind.hpp>

#include "boost/rete/action.hpp"
#include "boost/rete/instantiation.hpp"
#include "boost/rete/tuple.hpp"

namespace boost {
namespace rete {

void
agenda::store( tuple_handle const& th, action_ptr const& act_ptr) { 
	instantiation_ptr inst_ptr( instantiation::create( th, act_ptr) );
	boost::signals::connection con( 
		_cs.connect(
			act_ptr->priority(),
			boost::bind(
				& instantiation::operator(),
				inst_ptr) ) );
	inst_ptr->_con = con;
	th->_cons.push_back( con);
}

void 
agenda::add( tuple_handle const& th, action_ptr const& act_ptr) {
    store( th, act_ptr);
}

void
agenda::fire() {
    while ( ! empty() ) _cs();
}

inline 
bool
agenda::empty() const {
    return _cs.empty();
}

void
agenda::clear() {
    _cs.disconnect_all_slots();
}

}}
