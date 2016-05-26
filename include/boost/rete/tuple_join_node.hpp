
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_TUPLE_JOIN_NODE_H
#define BOOST_RETE_TUPLE_JOIN_NODE_H

#include <list>
#include <set>
#include <functional>

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

class alpha_memory;
class one_input_node;
class tuple_node;
class tuple_join_node;

typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;
typedef boost::shared_ptr< tuple_node >			tuple_node_ptr;
typedef boost::shared_ptr< tuple_join_node >	tuple_join_node_ptr;

class BOOST_RETE_DECL tuple_join_node {
private:
	typedef boost::signals2::signal< void ( tuple_handle &) >		children_sig_type;
	typedef boost::signals2::signal<
        tuple_handle(),
        aggregate_values< std::list< tuple_handle > >
    >		                                            th_sig_type;

	friend class tuple_node;
	friend class one_input_node;
	friend class alpha_memory;

	children_sig_type							_children;
	std::list< boost::signals2::connection >		_cons;
	th_sig_type									_items;
	th_sig_type	&								_left_items;
	th_sig_type	&								_right_items;
	std::set< declaration >						_decls;

	tuple_join_node( tuple_node_ptr const&, tuple_node_ptr const&);
	tuple_join_node( tuple_join_node_ptr const&, tuple_node_ptr const&);

	void store( tuple_handle const&);

	class apply : public std::unary_function< tuple_handle const&, void > {
	private:
		tuple_join_node &		_pn;
		tuple_handle const&		_th;

	public:
		apply( tuple_join_node &, tuple_handle const&);

		void operator()( argument_type);
	};

public:
	static tuple_join_node_ptr create( tuple_node_ptr const&, tuple_node_ptr const&);
	static tuple_join_node_ptr create( tuple_join_node_ptr const&, tuple_node_ptr const&);

	void left_activate( tuple_handle &);
	void right_activate( tuple_handle &);

	void attach( one_input_node_ptr const&);
	void attach( tuple_join_node_ptr const&);
	void detach();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_TUPLE_JOIN_NODE_H

