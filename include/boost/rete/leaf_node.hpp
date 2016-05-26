
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_LEAF_NODE_H
#define BOOST_RETE_LEAF_NODE_H

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <boost/rete/action.hpp>
#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class tuple;
class agenda;
class alpha_memory;
class one_input_node;
class two_input_node;
class negative_node;
class leaf_node;

typedef boost::shared_ptr< tuple >				tuple_handle;
typedef boost::shared_ptr< agenda >				agenda_ptr;
typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;
typedef boost::shared_ptr< two_input_node >		two_input_node_ptr;
typedef boost::shared_ptr< negative_node >		negative_node_ptr;
typedef boost::shared_ptr< leaf_node >			leaf_node_ptr;

class BOOST_RETE_DECL leaf_node {
private:
	friend class alpha_memory;
	friend class two_input_node;
	friend class negative_node;

	std::list< boost::signals2::connection > 	_cons;
	agenda_ptr									_ag_ptr;
	action_ptr									_act_ptr;

	leaf_node( agenda_ptr const&, action_ptr const&);

public:
	static leaf_node_ptr create( one_input_node_ptr &, agenda_ptr const&, action_ptr const&);
	static leaf_node_ptr create( two_input_node_ptr &, agenda_ptr const&, action_ptr const&);
	static leaf_node_ptr create( negative_node_ptr &, agenda_ptr const&, action_ptr const&);

	void activate( tuple_handle &);

	void detach();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_LEAF_NODE_H
