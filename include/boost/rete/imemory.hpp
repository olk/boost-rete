
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_IMEMORY_H
#define BOOST_RETE_IMEMORY_H

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class fact;

typedef boost::shared_ptr< fact >	fact_handle;

class BOOST_RETE_DECL imemory {	
public:
	virtual ~imemory() {};

	virtual void clear() = 0;
	virtual void add( fact_handle) = 0;
	virtual void modify( fact_handle) = 0;
	virtual void remove( fact_handle) = 0;
	virtual void run() = 0;
};

typedef boost::shared_ptr< imemory >	memory_ptr;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_IMEMORY_H
