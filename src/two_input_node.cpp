
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/two_input_node.hpp"

#include <algorithm>

#include <boost/bind.hpp>

#include "boost/rete/alpha_memory.hpp"
#include "boost/rete/beta_memory.hpp"
#include "boost/rete/leaf_node.hpp"
#include "boost/rete/one_input_node.hpp"
#include "boost/rete/tuple.hpp"

namespace boost {
namespace rete {

two_input_node::apply::apply( two_input_node const& tin, tuple_handle const& rth) :
    _tin( tin),
    _rth( rth)
{}

void
two_input_node::apply::operator()( tuple_handle const& lth) {
	if ( _tin._decls_shared.empty() ) {
		tuple_handle th( tuple::create( lth, _rth) );
		_tin._children( th);
	} else {
		if ( _tin.test( lth, _rth) )
		{
			tuple_handle th( tuple::create( lth, _rth) );
			_tin._children( th);
		}
	}
}

two_input_node::two_input_node( one_input_node_ptr const& oin_ptr) :
    _children(),
    _cons(),
    _decls( oin_ptr->_am_ptr->_decls),
    _decls_shared(),
    _am_ptr( oin_ptr->_am_ptr),
    _bm_ptr()
{}

two_input_node::two_input_node( beta_memory_ptr const& bm_ptr, one_input_node_ptr const& oin_ptr) :
    _children(),
    _cons(),
    _decls(),
    _decls_shared(),
    _am_ptr( oin_ptr->_am_ptr),
    _bm_ptr( bm_ptr) {
	std::merge(
		bm_ptr->_decls.begin(),
		bm_ptr->_decls.end(),
		oin_ptr->_am_ptr->_decls.begin(),
		oin_ptr->_am_ptr->_decls.end(),
		std::inserter( _decls, _decls.end() ) );
	std::set_intersection(
		bm_ptr->_decls.begin(),
		bm_ptr->_decls.end(),
		oin_ptr->_am_ptr->_decls.begin(),
		oin_ptr->_am_ptr->_decls.end(),
		std::inserter( _decls_shared, _decls_shared.end() ) );	
}

two_input_node_ptr 
two_input_node::create( one_input_node_ptr const& oin_ptr) { 
	two_input_node_ptr tin_ptr( new two_input_node( oin_ptr) ); 
	oin_ptr->_am_ptr->attach( tin_ptr);
	return tin_ptr;
}

two_input_node_ptr 
two_input_node::create( beta_memory_ptr const& bm_ptr, one_input_node_ptr const& oin_ptr) { 
	two_input_node_ptr tin_ptr( new two_input_node( bm_ptr, oin_ptr) ); 
	bm_ptr->attach( tin_ptr);
	oin_ptr->_am_ptr->attach( tin_ptr);
	return tin_ptr;
}

bool
two_input_node::test( tuple_handle const& lth, tuple_handle const& rth) const {
	std::set< declaration >::const_iterator i( _decls_shared.begin() );
	std::set< declaration >::const_iterator e( _decls_shared.end() );
						
	while ( i != e) {
		tuple::iterator li( lth->find( * i) );
		tuple::iterator ri( rth->find( * i) );

		bool bl = li == lth->end();
		bool br = ri == rth->end();
		if ( li == lth->end() || ri == rth->end() || ( * li) != ( * ri) )
			return false;
		++i;
	}

	return true;
}
	
void  
two_input_node::left_activate( tuple_handle & lth) {
	std::list< tuple_handle > lst( _am_ptr->_items() );
	std::for_each(
		lst.begin(),
		lst.end(),
		apply( * this, lth) );
}

void  
two_input_node::right_activate( tuple_handle & rth) {
	if( ! _bm_ptr) {
		_children( rth);
    } else {
		std::list< tuple_handle > lst( _bm_ptr->_items() );
		std::for_each(
			lst.begin(),
			lst.end(),
			apply( * this, rth) );
	}
}

void 
two_input_node::attach( leaf_node_ptr const& ln_ptr) { 
	ln_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& leaf_node::activate, 
				ln_ptr, 
				_1) ) );   
}

void 
two_input_node::attach( beta_memory_ptr const& bm_ptr) { 
	bm_ptr->_cons.push_back( 
			_children.connect( 
				boost::bind( 
					& beta_memory::activate, 
					bm_ptr, 
					_1) ) );  
}

void 
two_input_node::detach() { 
	std::for_each(
		_cons.begin(),
		_cons.end(),
		std::mem_fun_ref( 
			& boost::signals2::connection::disconnect) ); 
}

}}
