
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/tuple.hpp"

#include <stdexcept>
#include <algorithm>
#include <string>
#include <utility>

#include "boost/rete/fact.hpp"

namespace boost {
namespace rete {

tuple::apply::apply( tuple_handle const& th) : _th( th) {}

void
tuple::apply::operator()( argument_type arg) {
    arg.second.second->add( _th);
}

tuple::tuple( declaration const& decl, fact_handle const& fh) :
        _map(),
        _cons() {
	_map.insert( 
		map_type::value_type( 
			std::make_pair( 
				decl, 
				std::make_pair( 
					decl, 
					fh) ) ) );
}
	
tuple::tuple( tuple const& ltp, tuple const& rtp) :
        _map( ltp._map.size() > rtp._map.size() ? ltp._map : rtp._map),
        _cons() {
	if ( ltp._map.size() > rtp._map.size() ) {
		std::copy( 
			rtp._map.begin(), 
			rtp._map.end(), 
			std::inserter( _map, _map.end() ) );
	} else {
		std::copy( 
			ltp._map.begin(), 
			ltp._map.end(), 
			std::inserter( _map, _map.end() ) );
	}
}

tuple::tuple( tuple const& tp) :
    _map( tp._map),
    _cons()
{}

tuple_handle 
tuple::create( declaration const& decl, fact_handle const& fh) { 
	tuple_handle th( new tuple( decl, fh) ); 
	fh->add( th);
	return th;
}

tuple_handle 
tuple::create( tuple_handle const& lth, tuple_handle const& rth) { 
	tuple_handle th( new tuple( * lth, * rth) ); 
	std::for_each(
		th->_map.begin(),
		th->_map.end(),
		apply( th) );
	return th;
}

tuple_handle 
tuple::create( tuple const& ltp, tuple const& rtp) { 
	tuple_handle th( new tuple( ltp, rtp) ); 
	std::for_each(
		th->_map.begin(),
		th->_map.end(),
		apply( th) );
	return th;
}

tuple_handle 
tuple::create( tuple_handle const& th) {
    return tuple_handle( new tuple( * th) );
}

tuple::iterator
tuple::find( declaration const& decl) {
    return _map.find( decl);
}

tuple::iterator 
tuple::begin() {
    return _map.begin();
}

tuple::iterator 
tuple::end() {
    return _map.end();
}
	
void
tuple::detach() {
	std::for_each(
		_cons.begin(),
		_cons.end(),
		std::mem_fun_ref( 
			& boost::signals::connection::disconnect) );
}

adaptor::adaptor( tuple_handle const& th) : _th( th) {}

tuple_handle
adaptor::operator()() const {
    return _th;
}

}}
