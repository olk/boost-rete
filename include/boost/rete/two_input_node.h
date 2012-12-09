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
#ifndef OGX_RETE_TWO_INPUT_NODE_H
#define OGX_RETE_TWO_INPUT_NODE_H

#include <list>
#include <set>
#include <functional>

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <ogx/-rete/declaration.h>

namespace ogx
{
	namespace	rete
	{
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
		
		class two_input_node
		{
		private:
			typedef boost::signal< void( tuple_handle &) >	children_sig_type;
		
			friend class alpha_memory;
			friend class beta_memory;
			friend class leaf_node;
		
			children_sig_type							_children;
			std::list< boost::signals::connection > 	_cons;
			std::set< declaration >						_decls;
			std::set< declaration >						_decls_shared;
			alpha_memory_ptr							_am_ptr;
			beta_memory_ptr								_bm_ptr;
		
			two_input_node( one_input_node_ptr const&);
			two_input_node( beta_memory_ptr const&, one_input_node_ptr const&);
		
			bool test( tuple_handle const&, tuple_handle const&) const;
		
			class apply
			:
			public std::unary_function< tuple_handle const&, void >
			{
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
	}
};

#endif // OGX_RETE_TWO_INPUT_NODE_H
