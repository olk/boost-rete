
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/type_node.hpp"

#include <algorithm>

#include <boost/bind.hpp>

#include "boost/rete/fact.hpp"
#include "boost/rete/root_node.hpp"
#include "boost/rete/tuple_node.hpp"

namespace boost {
namespace rete {

type_node::type_node( std::string const& info) :
    _children(),
    _cons(),
    _info( info)
{}

type_node_ptr 
type_node::create( root_node_ptr const& rn_ptr, std::string const& info) { 
	type_node_ptr tn_ptr( new type_node( info) ); 
	rn_ptr->attach( tn_ptr);
	return tn_ptr;
}

bool 
type_node::instance_of( fact_handle const& fh) const {
    return std::string( fh->type().name() ).find( _info) != std::string::npos;
}

void
type_node::activate( fact_handle & fh) {
    if ( instance_of( fh) ) _children( fh);
}

void 
type_node::attach( tuple_node_ptr const& tn_ptr) { 
	tn_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& tuple_node::activate, 
				tn_ptr, 
				_1) ) ); 
}

void 
type_node::detach() { 
	std::for_each(
		_cons.begin(),
		_cons.end(),
		std::mem_fun_ref( 
			& boost::signals2::connection::disconnect) );
}

}}
