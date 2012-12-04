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
#ifndef OGX_RETE_ALPHA_MEMORY_H
#define OGX_RETE_ALPHA_MEMORY_H

#include <list>
#include <set>

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <ogx/rete/tuple.h>
#include <ogx/rete/declaration.h>

namespace ogx
{
	namespace rete
	{
		class tuple_node;
		class tuple_join_node;
		class two_input_node;
		class negative_node;
		class alpha_memory;
		class leaf_node;
		
		typedef boost::shared_ptr< tuple_node >			tuple_node_ptr;
		typedef boost::shared_ptr< tuple_join_node >	tuple_join_node_ptr;
		typedef boost::shared_ptr< two_input_node >		two_input_node_ptr;
		typedef boost::shared_ptr< negative_node >		negative_node_ptr;
		typedef boost::shared_ptr< leaf_node >			leaf_node_ptr;
		typedef boost::shared_ptr< alpha_memory >		alpha_memory_ptr;
		
		class alpha_memory
		{
		private:
			typedef boost::signal< void( tuple_handle &) >												children_sig_type;
			typedef boost::signal< tuple_handle (), aggregate_values< std::list< tuple_handle > > >		th_sig_type;
			
			friend class leaf_node;
			friend class two_input_node;
			friend class negative_node;
			
			children_sig_type			_children;
			th_sig_type					_items;
			std::set< declaration > 	_decls;
			
			alpha_memory( tuple_node_ptr const&);
			alpha_memory( tuple_join_node_ptr const&);
			
			void store( tuple_handle const&);
			
		public:
			static alpha_memory_ptr create( tuple_node_ptr const&);
			static alpha_memory_ptr create( tuple_join_node_ptr const&);
			
			void activate( tuple_handle &);
			
			void attach( leaf_node_ptr const&);
			void attach( two_input_node_ptr const&);
			void attach( negative_node_ptr const&);
		};
	}
};

#endif // OGX_RETE_ALPHA_MEMORY_H
