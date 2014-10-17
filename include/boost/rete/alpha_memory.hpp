
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_ALPHA_MEMORY_H
#define BOOST_RETE_ALPHA_MEMORY_H

#include <list>
#include <set>

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <boost/rete/declaration.hpp>
#include <boost/rete/detail/config.hpp>
#include <boost/rete/tuple.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class tuple_node;
class tuple_join_node;
class two_input_node;
class negative_node;
class alpha_memory;
class leaf_node;

typedef boost::shared_ptr< tuple_node >			tuple_node_ptr;
typedef boost::shared_ptr< tuple_join_node >	tuple_join_node_ptr;
typedef boost::shared_ptr< two_input_node >		two_input_node_ptr;
typedef boost::shared_ptr< negative_node >		negative_node_ptr;
typedef boost::shared_ptr< leaf_node >			leaf_node_ptr;
typedef boost::shared_ptr< alpha_memory >		alpha_memory_ptr;

class BOOST_RETE_DECL alpha_memory {
private:
	typedef boost::signal< void( tuple_handle &) >	    children_sig_type;
	typedef boost::signal<
        tuple_handle(),
        aggregate_values< std::list< tuple_handle > >
    >		                                            th_sig_type;
	
	friend class leaf_node;
	friend class two_input_node;
	friend class negative_node;
	
	children_sig_type			_children;
	th_sig_type					_items;
	std::set< declaration > 	_decls;
	
	alpha_memory( tuple_node_ptr const&);
	alpha_memory( tuple_join_node_ptr const&);
	
	void store( tuple_handle const&);
	
public:
	static alpha_memory_ptr create( tuple_node_ptr const&);
	static alpha_memory_ptr create( tuple_join_node_ptr const&);
	
	void activate( tuple_handle &);
	
	void attach( leaf_node_ptr const&);
	void attach( two_input_node_ptr const&);
	void attach( negative_node_ptr const&);
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_ALPHA_MEMORY_H
