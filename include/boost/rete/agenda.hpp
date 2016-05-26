
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_AGENDA_H
#define BOOST_RETE_AGENDA_H

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class tuple;
class action;

typedef boost::shared_ptr< tuple >		tuple_handle;
typedef boost::shared_ptr< action >		action_ptr;
	
class BOOST_RETE_DECL agenda {
private:
	struct topmost_only {
		typedef void result_type;
	
		template< typename InputIterator >
		result_type operator()( InputIterator first, InputIterator last) const {
            if ( first != last) {
                * first;
            }
        }
	};
	
	typedef boost::signals2::signal< void(), topmost_only >		cs_sig_type;
	
	cs_sig_type		_cs;
	
	void store( tuple_handle const&, action_ptr const&);
		
public:
	void add( tuple_handle const&, action_ptr const&);	
	void fire();	
	bool empty() const;
	void clear();
};

typedef boost::shared_ptr< agenda >		agenda_ptr;

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_AGENDA_H
