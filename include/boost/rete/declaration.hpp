
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_DECLARATION_H
#define BOOST_RETE_DECLARATION_H

#include <cstddef>
#include <string>
#include <typeinfo>

#include <boost/config.hpp>

#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class BOOST_RETE_DECL declaration {
private:
	friend bool operator<( declaration const&, declaration const&);
	friend bool operator>( declaration const&, declaration const&);
	friend bool operator==( declaration const&, declaration const&);
	friend bool operator!=( declaration const&, declaration const&);	

	std::string		_header;
	std::string		_vname;
	std::string		_info;

public:
	declaration( std::string const&, std::string const&, std::string const&);
	
	std::string const& get_header() const;
	std::string const& get_vname() const;
	std::string const& get_info() const;
};

bool operator<( declaration const&, declaration const&);
bool operator>( declaration const&, declaration const&);
bool operator==( declaration const&, declaration const&);
bool operator!=( declaration const&, declaration const&);

std::size_t hash_value( declaration const& decl);

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_DECLARATION_H
