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
#ifndef OGX_RETE_NEGATIVE_NODE_H
#define OGX_RETE_NEGATIVE_NODE_H

#include <list>
#include <set>
#include <functional>

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <ogx/rete/tuple.h>
#include <ogx/rete/declaration.h>

namespace ogx
{
	namespace rete
	{
		class alpha_memory;
		class beta_memory;
		class leaf_node;
		class one_input_node;
		class negative_node;
		
		typedef boost::shared_ptr< leaf_node >			leaf_node_ptr;
		typedef boost::shared_ptr< alpha_memory >		alpha_memory_ptr;
		typedef boost::shared_ptr< beta_memory >		beta_memory_ptr;
		typedef boost::shared_ptr< negative_node >		negative_node_ptr;
		typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;
		
		class negative_node
		{
		private:
			typedef boost::signal< void( tuple_handle &) >												children_sig_type;
			typedef boost::signal< tuple_handle (), aggregate_values< std::list< tuple_handle > > >		th_sig_type;
			
			friend class alpha_memory;
			friend class beta_memory;
			friend class leaf_node;
	
			children_sig_type							_children;
			std::list< boost::signals::connection > 	_cons;
			th_sig_type									_items;
			std::set< declaration >						_decls;
			std::set< declaration >						_decls_shared;
			alpha_memory_ptr							_am_ptr;
			beta_memory_ptr								_bm_ptr;
	
			negative_node( beta_memory_ptr const&, one_input_node_ptr const&);
	
			bool test( tuple_handle const&, tuple_handle const&) const;
	
			void store( tuple_handle &);
	
			class match_rigth
			:
			public std::unary_function< tuple_handle const&, void >
			{
			private:
				negative_node const&	_nn;
				tuple_handle const&		_lth;
				bool					_b;
				
			public:
				match_rigth( negative_node const&, tuple_handle const&);
				
				void operator()( argument_type);
				
				operator bool() const;
			};
			
			class match_left
			:
			public std::unary_function< tuple_handle const&, void >
			{
			private:
				negative_node const&	_nn;
				tuple_handle const&		_rth;
				
			public:
				match_left( negative_node const&, tuple_handle const&);
				
				void operator()( argument_type);
			};
		
		public:
			static negative_node_ptr create( beta_memory_ptr const&, one_input_node_ptr const&);
			
			void left_activate( tuple_handle &);
			void right_activate( tuple_handle &);
			
			void attach( leaf_node_ptr const&);
			void attach( beta_memory_ptr const&);
			void detach();
		};
	}
};

#endif // OGX_RETE_NEGATIVE_NODE_H
