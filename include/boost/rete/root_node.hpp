
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_ROOT_NODE_H
#define BOOST_RETE_ROOT_NODE_H

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class fact;
class type_node;
class root_node;

typedef boost::shared_ptr< fact >		fact_handle;
typedef boost::shared_ptr< type_node >	type_node_ptr;
typedef boost::shared_ptr< root_node >	root_node_ptr;

class BOOST_RETE_DECL root_node {
private:
	typedef boost::signals2::signal< void ( fact_handle &) >	children_sig_type;

	children_sig_type		_children;
	
	root_node();

public:
	static root_node_ptr create();

	void activate( fact_handle &);

	void attach( type_node_ptr const&);

	void clear();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_ROOT_NODE_H
