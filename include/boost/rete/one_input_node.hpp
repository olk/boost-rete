
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_ONE_INPUT_NODE_H
#define BOOST_RETE_ONE_INPUT_NODE_H

#include <list>

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class tuple;
class condition;
class alpha_memory;
class tuple_node;
class tuple_join_node;
class one_input_node;
class two_input_node;
class negative_node;
class leaf_node;

typedef boost::shared_ptr< tuple >				tuple_handle;
typedef boost::shared_ptr< condition >			condition_ptr;
typedef boost::shared_ptr< alpha_memory >		alpha_memory_ptr;
typedef boost::shared_ptr< tuple_node >			tuple_node_ptr;
typedef boost::shared_ptr< tuple_join_node >	tuple_join_node_ptr;
typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;

class BOOST_RETE_DECL one_input_node {
private:
	friend class tuple_node;
	friend class tuple_join_node;
	friend class leaf_node;
	friend class two_input_node;
	friend class negative_node;

	alpha_memory_ptr							_am_ptr;
	std::list< boost::signals::connection >		_cons;
	condition_ptr								_cond_ptr;

	one_input_node( tuple_node_ptr const&, condition_ptr const&);
	one_input_node( tuple_join_node_ptr const&, condition_ptr const&);

	bool eval( tuple_handle const&) const;

public:
	static one_input_node_ptr create( tuple_node_ptr const&, condition_ptr const&);
	static one_input_node_ptr create( tuple_join_node_ptr const&, condition_ptr const&);	

	void activate( tuple_handle &);

	void detach();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_ONE_INPUT_NODE_H
