
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/declaration.hpp"

#include <boost/functional/hash.hpp>

namespace boost {
namespace rete {

declaration::declaration( std::string const& header, 
						  std::string const& vname, 
						  std::string const& info) :
    _header( header),
    _vname( vname),
    _info( info)
{}

std::string const& 
declaration::get_header() const {
    return _header;
}

std::string const& 
declaration::get_vname() const {
    return _vname;
}

std::string const& 
declaration::get_info() const {
    return _info;
}

bool operator<( declaration const& decl1, declaration const& decl2) { 
	std::string s1( decl1._header + decl1._vname + decl1._info);
	std::string s2( decl2._header + decl2._vname + decl2._info);
	return s1 < s2; 
}

bool operator>( declaration const& decl1, declaration const& decl2) { 
	std::string s1( decl1._header + decl1._vname + decl1._info);
	std::string s2( decl2._header + decl2._vname + decl2._info);
	return s1 > s2;
}

bool operator==( declaration const& decl1, declaration const&decl2) { 
	std::string s1( decl1._header + decl1._vname + decl1._info);
	std::string s2( decl2._header + decl2._vname + decl2._info);
	return s1 == s2; 
}

bool operator!=( declaration const& decl1, declaration const& decl2) {
    return ! ( decl1 == decl2);
}

std::size_t hash_value( declaration const& decl) {
    boost::hash< std::string > hasher;
	std::string s( decl.get_info() + "-" + decl.get_vname() );
    return hasher( s);
}

}}
