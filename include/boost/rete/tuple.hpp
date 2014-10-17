
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef	BOOST_RETE_TUPLE_H
#define	BOOST_RETE_TUPLE_H

#include <functional>
#include <list>

#include <boost/config.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>
#include <boost/unordered_map.hpp> 

#include <boost/rete/declaration.hpp>
#include <boost/rete/detail/config.hpp>

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_PREFIX
#endif

namespace boost {
namespace rete {

class agenda;
class fact;
class tuple;
class tuple_node;
class tuple_join_node;
class negative_node;
class alpha_memory;
class beta_memory;

typedef boost::shared_ptr< fact >	fact_handle;
typedef boost::shared_ptr< tuple >	tuple_handle;

class BOOST_RETE_DECL tuple {
public:
	typedef unordered_map< declaration, std::pair< declaration, fact_handle > >		map_type;
	typedef map_type::iterator														iterator;

private:
	friend class agenda;
	friend class tuple_node;
	friend class tuple_join_node;
	friend class negative_node;
	friend class alpha_memory;
	friend class beta_memory;
	
	map_type									_map;
	std::list< boost::signals::connection >		_cons;
	
	tuple( declaration const&, fact_handle const&);
	tuple( tuple const&, tuple const&);
	tuple( tuple const&);
			
public:	
	class apply : public std::unary_function< map_type::value_type const&, void > {
	private:
		tuple_handle const&	_th;
		
	public:
		apply( tuple_handle const&);
		
		void operator()( argument_type);
	};  
		
	static tuple_handle create( declaration const&, fact_handle const&);
	static tuple_handle create( tuple_handle const&);
	static tuple_handle create( tuple_handle const&, tuple_handle const&);
	static tuple_handle create( tuple const&, tuple const&);
		
	iterator find( declaration const&);
	iterator begin();
	iterator end();

	void detach();
};

template< typename Container >
struct aggregate_values {
	typedef Container result_type;

	template< typename InputIterator >
	Container operator()( InputIterator first, InputIterator last) const
	{ return Container( first, last); }
};	

class adaptor {
private:
	tuple_handle	_th;

public:
	adaptor( tuple_handle const&);

	tuple_handle operator()() const;
};

}}

#ifdef BOOST_HAS_ABI_HEADERS
#  include BOOST_ABI_SUFFIX
#endif

#endif // BOOST_RETE_TUPLE_H
