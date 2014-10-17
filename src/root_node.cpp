
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/root_node.hpp"

#include <boost/bind.hpp>

#include "boost/rete/type_node.hpp"

namespace boost {
namespace rete {

root_node::root_node() :
_children(  )
{}

root_node_ptr 
root_node::create() {
    return root_node_ptr( new root_node() );
}

void
root_node::activate( fact_handle & fh) {
    _children( fh);
}

void 
root_node::attach( type_node_ptr const& tn_ptr) { 
	tn_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& type_node::activate, 
				tn_ptr, 
				_1) ) ); 
}

void
root_node::clear() {
    _children.disconnect_all_slots();
}

}}
