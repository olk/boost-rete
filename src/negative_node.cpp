
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/negative_node.hpp"

#include <algorithm>

#include <boost/bind.hpp>
#include <boost/mem_fn.hpp>

#include "boost/rete/alpha_memory.hpp"
#include "boost/rete/beta_memory.hpp"
#include "boost/rete/leaf_node.hpp"
#include "boost/rete/one_input_node.hpp"

namespace boost {
namespace rete {

negative_node::match_rigth::match_rigth( negative_node const& nn, tuple_handle const& lth) :
    _nn( nn),
    _lth( lth),
    _b( false)
{}

void
negative_node::match_rigth::operator()( tuple_handle const& rth) {
    if ( _nn.test( _lth, rth) ) _b = true;
}

negative_node::match_rigth::operator bool() const {
    return _b;
}

negative_node::match_left::match_left( negative_node const& nn, tuple_handle const& rth) :
    _nn( nn),
    _rth( rth)
{}

void
negative_node::match_left::operator()( tuple_handle const& lth) {
    if ( _nn.test( lth, _rth) ) lth->detach();
}

negative_node::negative_node( beta_memory_ptr const& bm_ptr, one_input_node_ptr const& oin_ptr) :
        _children(),
        _cons(),
        _items(),
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

negative_node_ptr 
negative_node::create( beta_memory_ptr const& bm_ptr, one_input_node_ptr const& oin_ptr) { 
	negative_node_ptr nn_ptr( new negative_node( bm_ptr, oin_ptr) ); 
	bm_ptr->attach( nn_ptr);
	oin_ptr->_am_ptr->attach( nn_ptr);
	return nn_ptr;
}

bool
negative_node::test( tuple_handle const& lth, tuple_handle const& rth) const {
	std::set< declaration >::const_iterator i( _decls_shared.begin() );
	std::set< declaration >::const_iterator e( _decls_shared.end() );

	while ( i != e) {
		tuple::iterator li( lth->find( * i) );
		tuple::iterator ri( rth->find( * i) );

		bool bl = ( li == lth->end() );
		bool br = ( ri == rth->end() );
		if ( li == lth->end() || ri == rth->end() || ( * li) != ( * ri) )
			return false;
		++i;
	}

	return true;
}

void 
negative_node::store( tuple_handle & th) { 
	th->_cons.push_back( 
		_items.connect(
			adaptor( th) ) ); 
}

void  
negative_node::left_activate( tuple_handle & lth) {
	if ( _am_ptr->_items.empty() ) {
		tuple_handle th( tuple::create( lth) );
		store( th);
		_children( th);
	} else {
		if ( _decls_shared.empty() ) {
			std::list< tuple_handle > lst( _items() );
			std::for_each(
				lst.begin(),
				lst.end(),
				boost::mem_fn( & tuple::detach) ); 
		} else {
			std::list< tuple_handle > lst( _am_ptr->_items() );
			if ( ! std::for_each(
						lst.begin(),
						lst.end(),
						match_rigth( * this, lth) ) ) {
				store( lth);
				_children( lth);
			}
		}
	}
}

void  
negative_node::right_activate( tuple_handle & rth) {
	if ( _decls_shared.empty() ) {
		std::list< tuple_handle > lst( _items() );
		std::for_each(
			lst.begin(),
			lst.end(),
			boost::mem_fn( & tuple::detach) ); 
	} else {
		std::list< tuple_handle > lst( _items() );
		std::for_each(
			lst.begin(),
			lst.end(),
			match_left( * this, rth) );
	}
}

void 
negative_node::attach( leaf_node_ptr const& ln_ptr) { 
	ln_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& leaf_node::activate, 
				ln_ptr, 
				_1) ) );   
}

void 
negative_node::attach( beta_memory_ptr const& bm_ptr) { 
	bm_ptr->_cons.push_back( 
		_children.connect( 
			boost::bind( 
				& beta_memory::activate, 
				bm_ptr, 
				_1) ) );  
}

void 
negative_node::detach() { 
	std::for_each(
		_cons.begin(),
		_cons.end(),
		std::mem_fun_ref( 
			& boost::signals::connection::disconnect) ); 
}

}}

