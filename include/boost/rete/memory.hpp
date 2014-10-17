
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_MEMORY_H
#define BOOST_RETE_MEMORY_H

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>

#include <boost/rete/agenda.hpp>
#include <boost/rete/detail/config.hpp>
#include <boost/rete/imemory.hpp>
#include <boost/rete/root_node.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class fact;

typedef boost::shared_ptr< fact >	fact_handle;

template< typename Agenda >
class memory : public imemory {
private:
	typedef boost::shared_ptr< Agenda > agenda_ptr;	    
		
	agenda_ptr		_ag_ptr;
	root_node_ptr	_rn_ptr;	

public:
	memory( agenda_ptr const& ag_ptr, root_node_ptr const& rn_ptr) : 
        imemory(),
        _ag_ptr( ag_ptr),
        _rn_ptr( rn_ptr)    
	{}

	~memory() {}

	void clear() { 
		_rn_ptr->clear();
		_ag_ptr->clear(); 
	}

	void add( fact_handle fh) {
        _rn_ptr->activate( fh);
    }

	void modify( fact_handle fh) {
		remove( fh);
		add( fh);
	}

	void remove( fact_handle fh) {
        fh->remove();
    }

	void run() {
        _ag_ptr->fire();
    }
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_MEMORY_H
