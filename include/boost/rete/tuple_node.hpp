
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_TUPLE_NODE_H
#define BOOST_RETE_TUPLE_NODE_H

#include <list>

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <boost/rete/declaration.hpp>
#include <boost/rete/detail/config.hpp>
#include <boost/rete/tuple.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class fact;
class type_node;
class tuple_join_node;
class one_input_node;
class tuple_node;
class alpha_memory;

typedef boost::shared_ptr< fact >				fact_handle;
typedef boost::shared_ptr< type_node >			type_node_ptr;
typedef boost::shared_ptr< tuple_join_node >	tuple_join_node_ptr;
typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;
typedef boost::shared_ptr< tuple_node >			tuple_node_ptr;

class BOOST_RETE_DECL tuple_node {
private:	
	typedef boost::signals2::signal< void ( tuple_handle &) >		children_sig_type;
	typedef boost::signals2::signal<
        tuple_handle(),
        aggregate_values< std::list< tuple_handle > >
    >		                                            th_sig_type;

	friend class alpha_memory;
	friend class type_node;
	friend class tuple_join_node;

	children_sig_type							_children;
	std::list< boost::signals2::connection >		_cons;
	th_sig_type									_items;
	declaration									_decl;

	tuple_node( declaration const&);

	void store( tuple_handle const&);

public:
	static tuple_node_ptr create( type_node_ptr const&, declaration const&);

	void activate( fact_handle &);

	void left_attach( tuple_join_node_ptr const&);
	void right_attach( tuple_join_node_ptr const&);
	void attach( one_input_node_ptr const&);
	void detach();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_TUPLE_NODE_H
