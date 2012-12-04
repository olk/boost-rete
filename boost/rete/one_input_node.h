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
#ifndef OGX_RETE_ONE_INPUT_NODE_H
#define OGX_RETE_ONE_INPUT_NODE_H

#include <list>

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

namespace ogx
{
	namespace rete
	{
		class tuple;
		class condition;
		class alpha_memory;
		class tuple_node;
		class tuple_join_node;
		class one_input_node;
		class two_input_node;
		class negative_node;
		class leaf_node;
		
		typedef boost::shared_ptr< tuple >				tuple_handle;
		typedef boost::shared_ptr< condition >			condition_ptr;
		typedef boost::shared_ptr< alpha_memory >		alpha_memory_ptr;
		typedef boost::shared_ptr< tuple_node >			tuple_node_ptr;
		typedef boost::shared_ptr< tuple_join_node >	tuple_join_node_ptr;
		typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;
		
		class one_input_node
		{
		private:
			friend class tuple_node;
			friend class tuple_join_node;
			friend class leaf_node;
			friend class two_input_node;
			friend class negative_node;
		
			alpha_memory_ptr							_am_ptr;
			std::list< boost::signals::connection >		_cons;
			condition_ptr								_cond_ptr;
		
			one_input_node( tuple_node_ptr const&, condition_ptr const&);
			one_input_node( tuple_join_node_ptr const&, condition_ptr const&);
		
			bool eval( tuple_handle const&) const;
		
		public:
			static one_input_node_ptr create( tuple_node_ptr const&, condition_ptr const&);
			static one_input_node_ptr create( tuple_join_node_ptr const&, condition_ptr const&);	
		
			void activate( tuple_handle &);
		
			void detach();
		};
	}
};

#endif // OGX_RETE_ONE_INPUT_NODE_H
