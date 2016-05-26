
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_TWO_INPUT_NODE_H
#define BOOST_RETE_TWO_INPUT_NODE_H

#include <list>
#include <set>
#include <functional>

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signals2.hpp>

#include <boost/rete/declaration.hpp>
#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class tuple;
class alpha_memory;
class beta_memory;
class leaf_node;
class one_input_node;
class two_input_node;

typedef boost::shared_ptr< tuple >				tuple_handle;
typedef boost::shared_ptr< leaf_node >			leaf_node_ptr;
typedef boost::shared_ptr< alpha_memory >		alpha_memory_ptr;
typedef boost::shared_ptr< beta_memory >		beta_memory_ptr;
typedef boost::shared_ptr< two_input_node >		two_input_node_ptr;
typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;

class BOOST_RETE_DECL two_input_node {
private:
	typedef boost::signals2::signal< void( tuple_handle &) >	children_sig_type;

	friend class alpha_memory;
	friend class beta_memory;
	friend class leaf_node;

	children_sig_type							_children;
	std::list< boost::signals2::connection > 	_cons;
	std::set< declaration >						_decls;
	std::set< declaration >						_decls_shared;
	alpha_memory_ptr							_am_ptr;
	beta_memory_ptr								_bm_ptr;

	two_input_node( one_input_node_ptr const&);
	two_input_node( beta_memory_ptr const&, one_input_node_ptr const&);

	bool test( tuple_handle const&, tuple_handle const&) const;

	class apply : public std::unary_function< tuple_handle const&, void > {
	private:
		two_input_node const&	_tin;
		tuple_handle const&		_rth;
	
	public:
		apply( two_input_node const&, tuple_handle const&);
	
		void operator()( argument_type);
	};

public:
	static two_input_node_ptr create( one_input_node_ptr const&);
	static two_input_node_ptr create( beta_memory_ptr const&, one_input_node_ptr const&);

	void left_activate( tuple_handle &);
	void right_activate( tuple_handle &);

	void attach( leaf_node_ptr const&);
	void attach( beta_memory_ptr const&);
	void detach();
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_TWO_INPUT_NODE_H
