
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/alpha_memory.hpp"

#include <algorithm>

#include <boost/bind.hpp>

#include "boost/rete/leaf_node.hpp"
#include "boost/rete/negative_node.hpp"
#include "boost/rete/tuple_join_node.hpp"
#include "boost/rete/tuple_node.hpp"
#include "boost/rete/two_input_node.hpp"

namespace boost {
namespace rete {

alpha_memory::alpha_memory( tuple_node_ptr const& tn_ptr) :
        _children(),
        _items(),
        _decls() {
    _decls.insert( tn_ptr->_decl);
}

alpha_memory::alpha_memory( tuple_join_node_ptr const& tjn_ptr) :
    _children(),
    _items(),
    _decls( tjn_ptr->_decls)
{}

alpha_memory_ptr
alpha_memory::create( tuple_node_ptr const& tn_ptr) {
    return alpha_memory_ptr( new alpha_memory( tn_ptr) );
}

alpha_memory_ptr
alpha_memory::create( tuple_join_node_ptr const& tjn_ptr) {
    return alpha_memory_ptr( new alpha_memory( tjn_ptr) );
}

void 
alpha_memory::activate( tuple_handle & th) { 
	store( th); 
	_children( th);
}
	
void 
alpha_memory::store( tuple_handle const& th) { 
	th->_cons.push_back( 
		_items.connect( 
			adaptor( th) ) ); 
}

void
alpha_memory::attach( leaf_node_ptr const& ln_ptr) { 
	ln_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& leaf_node::activate, 
				ln_ptr, 
				_1) ) );  
}

void
alpha_memory::attach( two_input_node_ptr const& tin_ptr) { 
	tin_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& two_input_node::right_activate, 
				tin_ptr, 
				_1) ) );  
}

void
alpha_memory::attach( negative_node_ptr const& nn_ptr) { 
	nn_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& negative_node::right_activate, 
				nn_ptr, 
				_1) ) );  
}

}}
