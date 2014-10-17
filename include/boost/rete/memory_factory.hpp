
//          Copyright Oliver Kowalke 2009.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_RETE_MEMORY_FACTORY_H
#define BOOST_RETE_MEMORY_FACTORY_H

#include <boost/rete/memory.hpp>
#include <boost/rete/fact.hpp>
#include <boost/rete/declaration.hpp>
#include <boost/rete/root_node.hpp>
#include <boost/rete/type_node.hpp>
#include <boost/rete/tuple_node.hpp>
#include <boost/rete/tuple_join_node.hpp>
#include <boost/rete/one_input_node.hpp>
#include <boost/rete/two_input_node.hpp>
#include <boost/rete/negative_node.hpp>
#include <boost/rete/alpha_memory.hpp>
#include <boost/rete/beta_memory.hpp>
#include <boost/rete/leaf_node.hpp>
#include <boost/rete/agenda.hpp>
#include <boost/rete/condition.hpp>
#include <boost/rete/action.hpp>

#include "fibonacci.h"

namespace boost {
namespace rete {

class cond_greater_zero : public boost::condition {
private:
	boost::memory_ptr		_mem_ptr;
	boost::declaration	_decl;
	
public:
	cond_greater_zero( boost::memory_ptr const& mem_ptr, boost::declaration const& decl) :
        _mem_ptr( mem_ptr),
        _decl( decl)
	{}

	bool operator()( boost::tuple_handle const& th) { 
		boost::fact_handle fh_f = th->find( _decl)->second.second;
		int f = boost::fact_cast< int >( fh_f);
		return f > 0; 
	}    
};

class cond_eq_five : public boost::condition {
private:
	boost::memory_ptr		_mem_ptr;
	boost::declaration	_decl;
	
public:
	cond_eq_five( boost::memory_ptr const& mem_ptr, boost::declaration const& decl) :
        _mem_ptr( mem_ptr),
        _decl( decl)
	{}

	bool operator()( boost::tuple_handle const& th) { 
		boost::fact_handle fh_f = th->find( _decl)->second.second;
		int f = boost::fact_cast< int >( fh_f);
		return f == 5; 
	}    
};

class cond_neq_five : public boost::condition {
private:
	boost::memory_ptr		_mem_ptr;
	boost::declaration	_decl;
	
public:
	cond_neq_five( boost::memory_ptr const& mem_ptr, boost::declaration const& decl) :
        _mem_ptr( mem_ptr),
        _decl( decl)
	{}

	bool operator()( boost::tuple_handle const& th) { 
		boost::fact_handle fh_f = th->find( _decl)->second.second;
		int f = boost::fact_cast< int >( fh_f);
		return f != 5; 
	}    
};

class print_1 : public boost::action {
private:
	long				_priority;
	boost::memory_ptr	_mem_ptr;
	boost::declaration	_decl;
	
public:
	print_1( long priority, 
            boost::memory_ptr const& mem_ptr, 
            boost::declaration const& decl) :
        _priority( priority),
        _mem_ptr( mem_ptr),
        _decl( decl)
	{}
	
	void operator()( boost::tuple_handle & th) { 
		boost::fact_handle fh_f = th->find( _decl)->second.second;
		int f = boost::fact_cast< int >( fh_f);
		std::cout << f << std::endl; 
	}
	
	long priority() const {
        return _priority;
    }
};

class print_2 : public boost::action {
private:
	long				_priority;
	boost::memory_ptr	_mem_ptr;
	boost::declaration	_decl1;
	boost::declaration	_decl2;
	
public:
	print_2( long priority, 
            boost::memory_ptr const& mem_ptr, 
            boost::declaration const& decl1,
            boost::declaration const& decl2) :
        _priority( priority),
        _mem_ptr( mem_ptr),
        _decl1( decl1),
        _decl2( decl2)
	{}
	
	void operator()( boost::tuple_handle & th) { 
		boost::fact_handle fh_f1 = th->find( _decl1)->second.second;
		boost::fact_handle fh_f2 = th->find( _decl2)->second.second;
		int f1 = boost::fact_cast< int >( fh_f1);
		int f2 = boost::fact_cast< int >( fh_f2);
		std::cout << f1 << ", " << f2 << std::endl; 
	}
	
	long priority() const {
        return _priority;
    }
};

typedef boost::shared_ptr< cond_greater_zero >	cond_greater_zero_ptr;
typedef boost::shared_ptr< cond_eq_five >	    cond_eq_five_ptr;
typedef boost::shared_ptr< cond_neq_five >	    cond_neq_five_ptr;
typedef boost::shared_ptr< print_1 >	        print_1_ptr;
typedef boost::shared_ptr< print_2 >	        print_2_ptr;
	
	
template < typename Loader, typename Agenda >
class memory_factory {
private:
	Loader _loader;
	
public:
	typedef memory< Agenda >			memory_type;
	
	memory_factory( Loader const &);	     
	memory_ptr operator()();
};
		
/////////////////////////////////////////////////////////////////////////////////////////////
		
template < typename Loader, typename Agenda >
memory_factory< Loader, Agenda >::memory_factory( Loader const & l) :
    _loader( l)
{}

template < typename Loader, typename Agenda >
memory_ptr
memory_factory< Loader, Agenda >::operator()() {
	agenda_ptr ag_ptr( new Agenda);
	boost::root_node_ptr root_n( boost::root_node::create() );
	memory_ptr mem_ptr( new memory_type( ag_ptr, root_n) );
	/*		
			boost::type_node_ptr typ_n( 
				boost::type_node::create( 
					root_n, 
					"int") );
		
			boost::declaration decl1("", "f1", "int");	
			boost::declaration decl2("", "f2", "int");
	
			boost::tuple_node_ptr tuple_n_f1( boost::tuple_node::create( typ_n, decl1) ); 
			boost::tuple_node_ptr tuple_n_f2( boost::tuple_node::create( typ_n, decl2) );
			
			boost::one_input_node_ptr oi_n_1( 
				boost::one_input_node::create( tuple_n_f1, 
							cond_greater_zero_ptr( 
								new cond_greater_zero( 
									mem_ptr, 
									decl1) ) ) );	
			boost::one_input_node_ptr oi_n_2( 
				boost::one_input_node::create( tuple_n_f1, 
							cond_eq_five_ptr( 
								new cond_eq_five( 
									mem_ptr, 
									decl1) ) ) );	
									
			boost::two_input_node_ptr tin_1(
				boost::two_input_node::create( oi_n_1) );
			boost::beta_memory_ptr bm1(
				boost::beta_memory::create( tin_1) );
			boost::negative_node_ptr nn(
				boost::negative_node::create( bm1, oi_n_2) );
									
			boost::leaf_node_ptr l_n( 
				boost::leaf_node::create( nn, 
							ag_ptr, 
							print_1_ptr( 
								new print_1( 
									0, 
									mem_ptr, 
									decl1) ) ) ); 
	*/
	boost::type_node_ptr typ_n( 
		boost::type_node::create( 
			root_n, 
			"fibonacci" /* typeid( fibonacci) */ ) );   
// parameters ////////////////////////////////////////////////////////////////////////////////
	boost::declaration decl("", "f", "fibonacci" /* typeid( fibonacci) */ );
	boost::declaration decl1("", "f1", "fibonacci" /* typeid( fibonacci) */ );	
	boost::declaration decl2("", "f2", "fibonacci" /* typeid( fibonacci) */ );
	boost::declaration decl3("", "f3", "fibonacci" /* typeid( fibonacci) */ );
	
	boost::tuple_node_ptr tuple_n_f( boost::tuple_node::create( typ_n, decl) ); 
	boost::tuple_node_ptr tuple_n_f1( boost::tuple_node::create( typ_n, decl1) ); 
	boost::tuple_node_ptr tuple_n_f2( boost::tuple_node::create( typ_n, decl2) ); 
	boost::tuple_node_ptr tuple_n_f3( boost::tuple_node::create( typ_n, decl3) ); 
	
	boost::tuple_join_node_ptr tj_n_1( boost::tuple_join_node::create( tuple_n_f1, tuple_n_f2) );
	boost::tuple_join_node_ptr tj_n_2( boost::tuple_join_node::create( tuple_n_f2, tuple_n_f3) ); 
	
// alpha memory //////////////////////////////////////////////////////////////////////////////
	boost::one_input_node_ptr oi_n_1( 
		boost::one_input_node::create( tuple_n_f, 
					cond_value_eq_neg_one_ptr( 
						new cond_value_eq_neg_one( 
							mem_ptr, 
							decl) ) ) );	
	boost::one_input_node_ptr oi_n_2( 
		boost::one_input_node::create( tuple_n_f, 
					cond_sequence_greater_one_ptr( 
						new cond_sequence_greater_one( 
							mem_ptr, 
							decl) ) ) );
	boost::one_input_node_ptr oi_n_3( 
		boost::one_input_node::create( tuple_n_f, 
					cond_sequence_eq_i_ptr( 
						new cond_sequence_eq_i( 
							mem_ptr, 
							decl, 
							1) ) ) );	
	boost::one_input_node_ptr oi_n_4( 
		boost::one_input_node::create( tuple_n_f, 
					cond_sequence_eq_i_ptr( 
						new cond_sequence_eq_i( 
							mem_ptr, 
							decl, 
							2) ) ) );
	boost::one_input_node_ptr oi_n_5( 
		boost::one_input_node::create( tj_n_1, 
					cond_sequence_add_one_ptr( 
						new cond_sequence_add_one( 
						mem_ptr, 
							decl1,
							decl2) ) ) );
	boost::one_input_node_ptr oi_n_6( 
		boost::one_input_node::create( tj_n_2, 
					cond_sequence_add_one_ptr( 
						new cond_sequence_add_one( 
						mem_ptr, 
							decl2,
							decl3) ) ) );
	boost::one_input_node_ptr oi_n_7( 
		boost::one_input_node::create( tuple_n_f1, 
					cond_value_neq_neg_one_ptr( 
						new cond_value_neq_neg_one( 
							mem_ptr, 
							decl1) ) ) );
	boost::one_input_node_ptr oi_n_8( 
		boost::one_input_node::create( tuple_n_f2, 
					cond_value_neq_neg_one_ptr( 
						new cond_value_neq_neg_one( 
							mem_ptr, 
							decl2) ) ) );
	boost::one_input_node_ptr oi_n_9( 
		boost::one_input_node::create( tuple_n_f3, 
					cond_value_eq_neg_one_ptr( 
						new cond_value_eq_neg_one( 
							mem_ptr, 
							decl3) ) ) );
	
// beta memory ////////////////////////////////////////////////////////////////////////////////
	boost::two_input_node_ptr tin_1(
		boost::two_input_node::create( oi_n_1) );
	boost::beta_memory_ptr bm1(
		boost::beta_memory::create( tin_1) );
	boost::two_input_node_ptr tin_2(
		boost::two_input_node::create( bm1, oi_n_2) );
	boost::two_input_node_ptr tin_3(
		boost::two_input_node::create( bm1, oi_n_3) );
	boost::two_input_node_ptr tin_4(
		boost::two_input_node::create( bm1, oi_n_4) );	
	boost::two_input_node_ptr tin_5(
		boost::two_input_node::create( oi_n_5) );
	boost::beta_memory_ptr bm2(
		boost::beta_memory::create( tin_5) );
	boost::two_input_node_ptr tin_6(
		boost::two_input_node::create( bm2, oi_n_6) );
	boost::beta_memory_ptr bm3(
		boost::beta_memory::create( tin_6) );
	boost::two_input_node_ptr tin_7(
		boost::two_input_node::create( bm3, oi_n_7) );
	boost::beta_memory_ptr bm4(
		boost::beta_memory::create( tin_7) );
	boost::two_input_node_ptr tin_8(
		boost::two_input_node::create( bm4, oi_n_8) );
	boost::beta_memory_ptr bm5(
		boost::beta_memory::create( tin_8) );
	boost::two_input_node_ptr tin_9(
		boost::two_input_node::create( bm5, oi_n_9) );
	
// leaf nodes ////////////////////////////////////////////////////////////////////////////////
	boost::leaf_node_ptr l_n_recurse( 
		boost::leaf_node::create( tin_2, 
					ag_ptr, 
					recurse_ptr( 
						new recurse( 
							0, 
							mem_ptr, 
							decl) ) ) );
	boost::leaf_node_ptr l_n_bootstrap1( 
		boost::leaf_node::create( tin_3, 
					ag_ptr, 
					bootstrap_ptr( 
						new bootstrap( 
							1, 
							mem_ptr, 
							decl) ) ) );
	boost::leaf_node_ptr l_n_bootstrap2( 
		boost::leaf_node::create( tin_4, 
					ag_ptr, 
					bootstrap_ptr( 
						new bootstrap( 
							2, 
							mem_ptr, 
							decl) ) ) );
	boost::leaf_node_ptr l_n_calculate( 
		boost::leaf_node::create( tin_9, 
					ag_ptr, 
					calculate_ptr( 
						new calculate( 
							0, 
							mem_ptr, 
							decl1,
							decl2,
							decl3) ) ) ); 
										
	return mem_ptr;
}

}}

#endif // BOOST_RETE_MEMORY_FACTORY_H
