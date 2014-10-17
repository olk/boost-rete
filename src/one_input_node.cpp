
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/one_input_node.hpp"

#include <algorithm>

#include "boost/rete/alpha_memory.hpp"
#include "boost/rete/condition.hpp"
#include "boost/rete/tuple_join_node.hpp"
#include "boost/rete/tuple_node.hpp"

namespace boost {
namespace rete {

one_input_node::one_input_node( tuple_node_ptr const& tn_ptr, condition_ptr const& cond_ptr) :
    _am_ptr( alpha_memory::create( tn_ptr) ),
    _cons(),
    _cond_ptr( cond_ptr)
{}

one_input_node::one_input_node( tuple_join_node_ptr const& tjn_ptr, condition_ptr const& cond_ptr) :
    _am_ptr( alpha_memory::create( tjn_ptr) ),
    _cons(),
    _cond_ptr( cond_ptr)
{}

one_input_node_ptr 
one_input_node::create( tuple_node_ptr const& tn_ptr, condition_ptr const& cond_ptr) { 
	one_input_node_ptr oin_ptr( new one_input_node( tn_ptr, cond_ptr) );
	tn_ptr->attach( oin_ptr);
	return oin_ptr;
}

one_input_node_ptr 
one_input_node::create( tuple_join_node_ptr const& tjn_ptr, condition_ptr const& cond_ptr) { 
	one_input_node_ptr oin_ptr( new one_input_node( tjn_ptr, cond_ptr) );
	tjn_ptr->attach( oin_ptr);
	return oin_ptr;
}

bool 
one_input_node::eval( tuple_handle const& th) const {
    return ( * _cond_ptr)( th);
}

void  
one_input_node::activate( tuple_handle & th) {
    if ( eval( th) ) _am_ptr->activate( th);
}

void 
one_input_node::detach() { 
	std::for_each(
		_cons.begin(),
		_cons.end(),
		std::mem_fun_ref( 
			& boost::signals::connection::disconnect) );
}

}}
