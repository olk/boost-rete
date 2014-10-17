
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/tuple_node.hpp"

#include <algorithm>

#include <boost/bind.hpp>

#include "boost/rete/one_input_node.hpp"
#include "boost/rete/tuple.hpp"
#include "boost/rete/tuple_join_node.hpp"
#include "boost/rete/type_node.hpp"

namespace boost {
namespace rete {

tuple_node::tuple_node( declaration const& decl) :
    _children(),
    _cons(),
    _items(),
    _decl( decl)
{}

tuple_node_ptr
tuple_node::create( type_node_ptr const& tn_ptr, declaration const& decl) {
	tuple_node_ptr _tn_ptr( new tuple_node( decl) );
	tn_ptr->attach( _tn_ptr); 
	return _tn_ptr;
}

void 
tuple_node::activate( fact_handle & fh) { 
	tuple_handle th( tuple::create( _decl, fh) );
	store( th);
	_children( th); 
}   

void 
tuple_node::store( tuple_handle const& th) {	
	th->_cons.push_back( 
		_items.connect(
			adaptor( th) ) ); 
}

void 
tuple_node::left_attach( tuple_join_node_ptr const& tjn_ptr) { 
	tjn_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& tuple_join_node::left_activate, 
				tjn_ptr, 
				_1) ) );  
}

void 
tuple_node::right_attach( tuple_join_node_ptr const& tjn_ptr) { 
	tjn_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& tuple_join_node::right_activate, 
				tjn_ptr, 
				_1) ) );  
}

void 
tuple_node::attach( one_input_node_ptr const& oin_ptr) { 
	oin_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& one_input_node::activate, 
				oin_ptr, 
				_1) ) );  
}

void 
tuple_node::detach() { 
	std::for_each(
		_cons.begin(),
		_cons.end(),
		std::mem_fun_ref( 
			& boost::signals::connection::disconnect) ); 
}

}}
