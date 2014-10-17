
//          Copyright Oliver Kowalke 2013.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#include "boost/rete/loader.hpp"

#include <stdexcept>
#include <fstream>

#include <boost/spirit/iterator/file_iterator.hpp>

namespace boost {
namespace rete {

loader::loader( std::string const & filename) :
    _filename( filename)
{}

inline
loader::result_type
loader::operator()() {
	boost::spirit::file_iterator<> first( _filename);

	if ( ! first)
		throw std::runtime_error("failure by open the file '" + _filename + "'");

	boost::spirit::file_iterator<> last = first.make_end();
	
	return std::string( first, last);
}

}}
