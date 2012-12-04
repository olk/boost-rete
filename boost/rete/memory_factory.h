/***************************************************************************
 *   Copyright (C) 2004 by Oliver Kowalke                                  *
 *   oliver.kowalke@t-online.de                                            *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/
#ifndef OGX_RETE_MEMORY_FACTORY_H
#define OGX_RETE_MEMORY_FACTORY_H

#include <ogx/rete/memory.h>
#include <ogx/rete/memory.h>
#include <ogx/rete/fact.h>
#include <ogx/rete/declaration.h>
#include <ogx/rete/root_node.h>
#include <ogx/rete/type_node.h>
#include <ogx/rete/tuple_node.h>
#include <ogx/rete/tuple_join_node.h>
#include <ogx/rete/one_input_node.h>
#include <ogx/rete/two_input_node.h>
#include <ogx/rete/negative_node.h>
#include <ogx/rete/alpha_memory.h>
#include <ogx/rete/beta_memory.h>
#include <ogx/rete/leaf_node.h>
#include <ogx/rete/agenda.h>
#include <ogx/rete/condition.h>
#include <ogx/rete/action.h>

#include "fibonacci.h"

namespace ogx
{
	namespace rete
	{
		class cond_greater_zero
		:
		public ogx::condition
		{
		private:
			ogx::memory_ptr		_mem_ptr;
			ogx::declaration	_decl;
			
		public:
			cond_greater_zero( ogx::memory_ptr const& mem_ptr, ogx::declaration const& decl) 
			:
			_mem_ptr( mem_ptr),
			_decl( decl)
			{}
		
			bool operator()( ogx::tuple_handle const& th)
			{ 
				ogx::fact_handle fh_f = th->find( _decl)->second.second;
				
				int f = ogx::fact_cast< int >( fh_f);
				
				return f > 0; 
			}    
		};
		
		class cond_eq_five
		:
		public ogx::condition
		{
		private:
			ogx::memory_ptr		_mem_ptr;
			ogx::declaration	_decl;
			
		public:
			cond_eq_five( ogx::memory_ptr const& mem_ptr, ogx::declaration const& decl) 
			:
			_mem_ptr( mem_ptr),
			_decl( decl)
			{}
		
			bool operator()( ogx::tuple_handle const& th)
			{ 
				ogx::fact_handle fh_f = th->find( _decl)->second.second;
				
				int f = ogx::fact_cast< int >( fh_f);
				
				return f == 5; 
			}    
		};
		
		class cond_neq_five
		:
		public ogx::condition
		{
		private:
			ogx::memory_ptr		_mem_ptr;
			ogx::declaration	_decl;
			
		public:
			cond_neq_five( ogx::memory_ptr const& mem_ptr, ogx::declaration const& decl) 
			:
			_mem_ptr( mem_ptr),
			_decl( decl)
			{}
		
			bool operator()( ogx::tuple_handle const& th)
			{ 
				ogx::fact_handle fh_f = th->find( _decl)->second.second;
				
				int f = ogx::fact_cast< int >( fh_f);
				
				return f != 5; 
			}    
		};
		
		class print_1
		:
		public ogx::action
		{
		private:
			long				_priority;
			ogx::memory_ptr		_mem_ptr;
			ogx::declaration	_decl;
			
		public:
			print_1( long priority, 
				ogx::memory_ptr const& mem_ptr, 
				ogx::declaration const& decl) 
			:
			_priority( priority),
			_mem_ptr( mem_ptr),
			_decl( decl)
			{}
			
			void operator()( ogx::tuple_handle & th)
			{ 
				ogx::fact_handle fh_f = th->find( _decl)->second.second;
				
				int f = ogx::fact_cast< int >( fh_f);
				
				std::cout << f << std::endl; 
			}
			
			long priority() const
			{ return _priority; }
		};
		
		class print_2
		:
		public ogx::action
		{
		private:
			long				_priority;
			ogx::memory_ptr		_mem_ptr;
			ogx::declaration	_decl1;
			ogx::declaration	_decl2;
			
		public:
			print_2( long priority, 
				ogx::memory_ptr const& mem_ptr, 
				ogx::declaration const& decl1,
				ogx::declaration const& decl2) 
			:
			_priority( priority),
			_mem_ptr( mem_ptr),
			_decl1( decl1),
			_decl2( decl2)
			{}
			
			void operator()( ogx::tuple_handle & th)
			{ 
				ogx::fact_handle fh_f1 = th->find( _decl1)->second.second;
				ogx::fact_handle fh_f2 = th->find( _decl2)->second.second;
				
				int f1 = ogx::fact_cast< int >( fh_f1);
				int f2 = ogx::fact_cast< int >( fh_f2);
				
				std::cout << f1 << ", " << f2 << std::endl; 
			}
			
			long priority() const
			{ return _priority; }
		};
		
		typedef boost::shared_ptr< cond_greater_zero >	cond_greater_zero_ptr;
		typedef boost::shared_ptr< cond_eq_five >	cond_eq_five_ptr;
		typedef boost::shared_ptr< cond_neq_five >	cond_neq_five_ptr;
		typedef boost::shared_ptr< print_1 >	print_1_ptr;
		typedef boost::shared_ptr< print_2 >	print_2_ptr;
	
	
		template
		< 
			typename Loader,
			typename Agenda
		>
		class memory_factory
		{
		private:
			Loader _loader;
			
		public:
			typedef memory< Agenda >			memory_type;
			
			memory_factory( Loader const &);	     
			memory_ptr operator()();
		};
		
	/////////////////////////////////////////////////////////////////////////////////////////////
		
		template
		< 
			typename Loader,
			typename Agenda
		>
		memory_factory< Loader, Agenda >::memory_factory( Loader const & l)
		:
		_loader( l)
		{}
		
		template
		< 
			typename Loader,
			typename Agenda
		>
		inline
		memory_ptr
		memory_factory< Loader, Agenda >::operator()()
		{
			agenda_ptr ag_ptr( new Agenda);
						
			ogx::root_node_ptr root_n( ogx::root_node::create() );
		
			memory_ptr mem_ptr( new memory_type( ag_ptr, root_n) );
	/*		
			ogx::type_node_ptr typ_n( 
				ogx::type_node::create( 
					root_n, 
					"int") );
		
			ogx::declaration decl1("", "f1", "int");	
			ogx::declaration decl2("", "f2", "int");
	
			ogx::tuple_node_ptr tuple_n_f1( ogx::tuple_node::create( typ_n, decl1) ); 
			ogx::tuple_node_ptr tuple_n_f2( ogx::tuple_node::create( typ_n, decl2) );
			
			ogx::one_input_node_ptr oi_n_1( 
				ogx::one_input_node::create( tuple_n_f1, 
							cond_greater_zero_ptr( 
								new cond_greater_zero( 
									mem_ptr, 
									decl1) ) ) );	
			ogx::one_input_node_ptr oi_n_2( 
				ogx::one_input_node::create( tuple_n_f1, 
							cond_eq_five_ptr( 
								new cond_eq_five( 
									mem_ptr, 
									decl1) ) ) );	
									
			ogx::two_input_node_ptr tin_1(
				ogx::two_input_node::create( oi_n_1) );
			ogx::beta_memory_ptr bm1(
				ogx::beta_memory::create( tin_1) );
			ogx::negative_node_ptr nn(
				ogx::negative_node::create( bm1, oi_n_2) );
									
			ogx::leaf_node_ptr l_n( 
				ogx::leaf_node::create( nn, 
							ag_ptr, 
							print_1_ptr( 
								new print_1( 
									0, 
									mem_ptr, 
									decl1) ) ) ); 
	*/
			ogx::type_node_ptr typ_n( 
				ogx::type_node::create( 
					root_n, 
					"fibonacci" /* typeid( fibonacci) */ ) );   
	////// parameters ////////////////////////////////////////////////////////////////////////////////
			ogx::declaration decl("", "f", "fibonacci" /* typeid( fibonacci) */ );
			ogx::declaration decl1("", "f1", "fibonacci" /* typeid( fibonacci) */ );	
			ogx::declaration decl2("", "f2", "fibonacci" /* typeid( fibonacci) */ );
			ogx::declaration decl3("", "f3", "fibonacci" /* typeid( fibonacci) */ );
			
			ogx::tuple_node_ptr tuple_n_f( ogx::tuple_node::create( typ_n, decl) ); 
			ogx::tuple_node_ptr tuple_n_f1( ogx::tuple_node::create( typ_n, decl1) ); 
			ogx::tuple_node_ptr tuple_n_f2( ogx::tuple_node::create( typ_n, decl2) ); 
			ogx::tuple_node_ptr tuple_n_f3( ogx::tuple_node::create( typ_n, decl3) ); 
			
			ogx::tuple_join_node_ptr tj_n_1( ogx::tuple_join_node::create( tuple_n_f1, tuple_n_f2) );
			ogx::tuple_join_node_ptr tj_n_2( ogx::tuple_join_node::create( tuple_n_f2, tuple_n_f3) ); 
			
	////// alpha memory //////////////////////////////////////////////////////////////////////////////
			ogx::one_input_node_ptr oi_n_1( 
				ogx::one_input_node::create( tuple_n_f, 
							cond_value_eq_neg_one_ptr( 
								new cond_value_eq_neg_one( 
									mem_ptr, 
									decl) ) ) );	
			ogx::one_input_node_ptr oi_n_2( 
				ogx::one_input_node::create( tuple_n_f, 
							cond_sequence_greater_one_ptr( 
								new cond_sequence_greater_one( 
									mem_ptr, 
									decl) ) ) );
			ogx::one_input_node_ptr oi_n_3( 
				ogx::one_input_node::create( tuple_n_f, 
							cond_sequence_eq_i_ptr( 
								new cond_sequence_eq_i( 
									mem_ptr, 
									decl, 
									1) ) ) );	
			ogx::one_input_node_ptr oi_n_4( 
				ogx::one_input_node::create( tuple_n_f, 
							cond_sequence_eq_i_ptr( 
								new cond_sequence_eq_i( 
									mem_ptr, 
									decl, 
									2) ) ) );
			ogx::one_input_node_ptr oi_n_5( 
				ogx::one_input_node::create( tj_n_1, 
							cond_sequence_add_one_ptr( 
								new cond_sequence_add_one( 
								mem_ptr, 
									decl1,
									decl2) ) ) );
			ogx::one_input_node_ptr oi_n_6( 
				ogx::one_input_node::create( tj_n_2, 
							cond_sequence_add_one_ptr( 
								new cond_sequence_add_one( 
								mem_ptr, 
									decl2,
									decl3) ) ) );
			ogx::one_input_node_ptr oi_n_7( 
				ogx::one_input_node::create( tuple_n_f1, 
							cond_value_neq_neg_one_ptr( 
								new cond_value_neq_neg_one( 
									mem_ptr, 
									decl1) ) ) );
			ogx::one_input_node_ptr oi_n_8( 
				ogx::one_input_node::create( tuple_n_f2, 
							cond_value_neq_neg_one_ptr( 
								new cond_value_neq_neg_one( 
									mem_ptr, 
									decl2) ) ) );
			ogx::one_input_node_ptr oi_n_9( 
				ogx::one_input_node::create( tuple_n_f3, 
							cond_value_eq_neg_one_ptr( 
								new cond_value_eq_neg_one( 
									mem_ptr, 
									decl3) ) ) );
			
	////// beta memory ////////////////////////////////////////////////////////////////////////////////
			ogx::two_input_node_ptr tin_1(
				ogx::two_input_node::create( oi_n_1) );
			ogx::beta_memory_ptr bm1(
				ogx::beta_memory::create( tin_1) );
			ogx::two_input_node_ptr tin_2(
				ogx::two_input_node::create( bm1, oi_n_2) );
			ogx::two_input_node_ptr tin_3(
				ogx::two_input_node::create( bm1, oi_n_3) );
			ogx::two_input_node_ptr tin_4(
				ogx::two_input_node::create( bm1, oi_n_4) );	
			ogx::two_input_node_ptr tin_5(
				ogx::two_input_node::create( oi_n_5) );
			ogx::beta_memory_ptr bm2(
				ogx::beta_memory::create( tin_5) );
			ogx::two_input_node_ptr tin_6(
				ogx::two_input_node::create( bm2, oi_n_6) );
			ogx::beta_memory_ptr bm3(
				ogx::beta_memory::create( tin_6) );
			ogx::two_input_node_ptr tin_7(
				ogx::two_input_node::create( bm3, oi_n_7) );
			ogx::beta_memory_ptr bm4(
				ogx::beta_memory::create( tin_7) );
			ogx::two_input_node_ptr tin_8(
				ogx::two_input_node::create( bm4, oi_n_8) );
			ogx::beta_memory_ptr bm5(
				ogx::beta_memory::create( tin_8) );
			ogx::two_input_node_ptr tin_9(
				ogx::two_input_node::create( bm5, oi_n_9) );
			
	////// leaf nodes ////////////////////////////////////////////////////////////////////////////////
			ogx::leaf_node_ptr l_n_recurse( 
				ogx::leaf_node::create( tin_2, 
							ag_ptr, 
							recurse_ptr( 
								new recurse( 
									0, 
									mem_ptr, 
									decl) ) ) );
			ogx::leaf_node_ptr l_n_bootstrap1( 
				ogx::leaf_node::create( tin_3, 
							ag_ptr, 
							bootstrap_ptr( 
								new bootstrap( 
									1, 
									mem_ptr, 
									decl) ) ) );
			ogx::leaf_node_ptr l_n_bootstrap2( 
				ogx::leaf_node::create( tin_4, 
							ag_ptr, 
							bootstrap_ptr( 
								new bootstrap( 
									2, 
									mem_ptr, 
									decl) ) ) );
			ogx::leaf_node_ptr l_n_calculate( 
				ogx::leaf_node::create( tin_9, 
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
	}
};

#endif // OGX_RETE_MEMORY_FACTORY_H
