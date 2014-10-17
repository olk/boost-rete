
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/leaf_node.hpp"

#include <algorithm>

#include "boost/rete/agenda.hpp"
#include "boost/rete/alpha_memory.hpp"
#include "boost/rete/negative_node.hpp"
#include "boost/rete/one_input_node.hpp"
#include "boost/rete/two_input_node.hpp"

namespace boost {
namespace rete {

leaf_node::leaf_node( agenda_ptr const& ag_ptr, action_ptr const& act_ptr) :
    _cons(),
    _ag_ptr( ag_ptr),
    _act_ptr( act_ptr)
{}

leaf_node_ptr
leaf_node::create( one_input_node_ptr & oin_ptr, agenda_ptr const& ag_ptr, action_ptr const& act_ptr) {
	leaf_node_ptr ln_ptr( new leaf_node( ag_ptr, act_ptr) );
	oin_ptr->_am_ptr->attach( ln_ptr);
	return ln_ptr;
}

leaf_node_ptr
leaf_node::create( two_input_node_ptr & tin_ptr, agenda_ptr const& ag_ptr, action_ptr const& act_ptr) {
	leaf_node_ptr ln_ptr( new leaf_node( ag_ptr, act_ptr) );
	tin_ptr->attach( ln_ptr);
	return ln_ptr;
}

leaf_node_ptr
leaf_node::create( negative_node_ptr & nn_ptr, agenda_ptr const& ag_ptr, action_ptr const& act_ptr) {
	leaf_node_ptr ln_ptr( new leaf_node( ag_ptr, act_ptr) );
	nn_ptr->attach( ln_ptr);
	return ln_ptr;
}

void 
leaf_node::activate( tuple_handle & th) {
    _ag_ptr->add( th, _act_ptr);
}

void 
leaf_node::detach() { 
	std::for_each(
		_cons.begin(),
		_cons.end(),
		std::mem_fun_ref( 
			& boost::signals::connection::disconnect) ); 
}

}}
