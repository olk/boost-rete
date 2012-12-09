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
#ifndef OGX_RETE_TUPLE_NODE_H
#define OGX_RETE_TUPLE_NODE_H

#include <list>

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <ogx/rete/tuple.h>
#include <ogx/rete/declaration.h>

namespace ogx
{
	namespace rete
	{
		class fact;
		class type_node;
		class tuple_join_node;
		class one_input_node;
		class tuple_node;
		class alpha_memory;
		
		typedef boost::shared_ptr< fact >				fact_handle;
		typedef boost::shared_ptr< type_node >			type_node_ptr;
		typedef boost::shared_ptr< tuple_join_node >	tuple_join_node_ptr;
		typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;
		typedef boost::shared_ptr< tuple_node >			tuple_node_ptr;
		
		class tuple_node
		{
		private:	
			typedef boost::signal< void ( tuple_handle &) >												children_sig_type;
			typedef boost::signal< tuple_handle (), aggregate_values< std::list< tuple_handle > > >		th_sig_type;
		
			friend class alpha_memory;
			friend class type_node;
			friend class tuple_join_node;
		
			children_sig_type							_children;
			std::list< boost::signals::connection >		_cons;
			th_sig_type									_items;
			declaration									_decl;
		
			tuple_node( declaration const&);
		
			void store( tuple_handle const&);
		
		public:
			static tuple_node_ptr create( type_node_ptr const&, declaration const&);
		
			void activate( fact_handle &);
		
			void left_attach( tuple_join_node_ptr const&);
			void right_attach( tuple_join_node_ptr const&);
			void attach( one_input_node_ptr const&);
			void detach();
		};
	}
}

#endif // OGX_RETE_TUPLE_NODE_H
