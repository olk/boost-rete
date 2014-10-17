
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/instantiation.hpp"

namespace boost {
namespace rete {

instantiation::instantiation( tuple_handle const& th, action_ptr const& act_ptr) :
    _th( th),
    _act_ptr( act_ptr),
    _con()
{}

instantiation_ptr
instantiation::create( tuple_handle const& th, action_ptr const& act_ptr) {
    return instantiation_ptr( new instantiation( th, act_ptr) );
}

void 
instantiation::operator()() { 
	_con.disconnect();
	( * _act_ptr)( _th); 
}

}}
