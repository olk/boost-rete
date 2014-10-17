
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_LOADER_H
#define BOOST_RETE_LOADER_H

#include <string>
#include <functional>

#include <boost/config.hpp>

#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class BOOST_RETE_DECL loader : public std::unary_function< void, std::string > {
private:
	std::string		_filename;
	
public:
	loader( std::string const &);

	result_type operator()();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_LOADER_H
