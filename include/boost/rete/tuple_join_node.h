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
#ifndef OGX_RETE_TUPLE_JOIN_NODE_H
#define OGX_RETE_TUPLE_JOIN_NODE_H

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
		class one_input_node;
		class tuple_node;
		class tuple_join_node;
		
		typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;
		typedef boost::shared_ptr< tuple_node >			tuple_node_ptr;
		typedef boost::shared_ptr< tuple_join_node >	tuple_join_node_ptr;
		
		class tuple_join_node
		{
		private:
			typedef boost::signal< void ( tuple_handle &) >												children_sig_type;
			typedef boost::signal< tuple_handle(), aggregate_values< std::list< tuple_handle > > >		th_sig_type;
		
			friend class tuple_node;
			friend class one_input_node;
			friend class alpha_memory;
		
			children_sig_type							_children;
			std::list< boost::signals::connection >		_cons;
			th_sig_type									_items;
			th_sig_type	&								_left_items;
			th_sig_type	&								_right_items;
			std::set< declaration >						_decls;
		
			tuple_join_node( tuple_node_ptr const&, tuple_node_ptr const&);
			tuple_join_node( tuple_join_node_ptr const&, tuple_node_ptr const&);
		
			void store( tuple_handle const&);
		
			class apply
			:
			public std::unary_function< tuple_handle const&, void >
			{
			private:
				tuple_join_node &		_pn;
				tuple_handle const&		_th;
		
			public:
				apply( tuple_join_node &, tuple_handle const&);
		
				void operator()( argument_type);
			};
		
		public:
			static tuple_join_node_ptr create( tuple_node_ptr const&, tuple_node_ptr const&);
			static tuple_join_node_ptr create( tuple_join_node_ptr const&, tuple_node_ptr const&);
		
			void left_activate( tuple_handle &);
			void right_activate( tuple_handle &);
		
			void attach( one_input_node_ptr const&);
			void attach( tuple_join_node_ptr const&);
			void detach();
		};
	}
};

#endif // OGX_RETE_TUPLE_JOIN_NODE_H

