
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/beta_memory.hpp"

#include <algorithm>

#include <boost/bind.hpp>

#include "boost/rete/two_input_node.hpp"
#include "boost/rete/negative_node.hpp"

namespace boost {
namespace rete {

beta_memory::beta_memory( two_input_node_ptr const& tin_ptr) :
    _children(),
    _cons(),
    _items(),
    _decls( tin_ptr->_decls)
{}

beta_memory::beta_memory( negative_node_ptr const& nn_ptr) :
    _children(),
    _cons(),
    _items(),
    _decls( nn_ptr->_decls)
{}

beta_memory_ptr 
beta_memory::create( two_input_node_ptr const& tin_ptr) {
	beta_memory_ptr bm_ptr( new beta_memory( tin_ptr) );
	tin_ptr->attach( bm_ptr);
	return bm_ptr;
}

beta_memory_ptr 
beta_memory::create( negative_node_ptr const& nn_ptr) {
	beta_memory_ptr bm_ptr( new beta_memory( nn_ptr) );
	nn_ptr->attach( bm_ptr);
	return bm_ptr;
}

void 
beta_memory::activate( tuple_handle & th) { 
	store( th); 
	_children( th);
}

void 
beta_memory::store( tuple_handle & th) { 
	th->_cons.push_back( 
		_items.connect(
			adaptor( th) ) ); 
}

void 
beta_memory::attach( two_input_node_ptr const& tin_ptr) { 
	tin_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& two_input_node::left_activate, 
				tin_ptr, 
				_1) ) );  
}

void 
beta_memory::attach( negative_node_ptr const& nn_ptr) { 
	nn_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& negative_node::left_activate, 
				nn_ptr, 
				_1) ) );  
}

void 
beta_memory::detach() { 
	std::for_each(
		_cons.begin(),
		_cons.end(),
		std::mem_fun_ref( 
			& boost::signals2::connection::disconnect) ); 
}

}}
