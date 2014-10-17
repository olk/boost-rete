
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_TYPE_NODE_H
#define BOOST_RETE_TYPE_NODE_H

#include <list>
#include <typeinfo>

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class fact;
class tuple_node;
class root_node;
class type_node;

typedef boost::shared_ptr< fact >			fact_handle;
typedef boost::shared_ptr< tuple_node >		tuple_node_ptr;
typedef boost::shared_ptr< root_node >		root_node_ptr;
typedef boost::shared_ptr< type_node >		type_node_ptr;

class BOOST_RETE_DECL type_node {
private:
	typedef boost::signal< void ( fact_handle &) >	children_func_type;
	
	friend class root_node;

	children_func_type							_children;
	std::list< boost::signals::connection >		_cons;
	std::string									_info;

	type_node( std::string const&);

	bool instance_of( fact_handle const&) const;

public:
	static type_node_ptr create( root_node_ptr const&, std::string const&);
	
	void activate( fact_handle &);	
	
	void attach( tuple_node_ptr const&);
	void detach();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_TYPE_NODE_H
