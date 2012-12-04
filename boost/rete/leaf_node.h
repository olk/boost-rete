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
#ifndef OGX_RETE_LEAF_NODE_H
#define OGX_RETE_LEAF_NODE_H

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <ogx/rete/action.h>

namespace ogx
{
	namespace rete
	{
		class tuple;
		class agenda;
		class alpha_memory;
		class one_input_node;
		class two_input_node;
		class negative_node;
		class leaf_node;
		
		typedef boost::shared_ptr< tuple >				tuple_handle;
		typedef boost::shared_ptr< agenda >				agenda_ptr;
		typedef boost::shared_ptr< one_input_node >		one_input_node_ptr;
		typedef boost::shared_ptr< two_input_node >		two_input_node_ptr;
		typedef boost::shared_ptr< negative_node >		negative_node_ptr;
		typedef boost::shared_ptr< leaf_node >			leaf_node_ptr;
		
		class leaf_node
		{
		private:
			friend class alpha_memory;
			friend class two_input_node;
			friend class negative_node;
		
			std::list< boost::signals::connection > 	_cons;
			agenda_ptr									_ag_ptr;
			action_ptr									_act_ptr;
		
			leaf_node( agenda_ptr const&, action_ptr const&);
		
		public:
			static leaf_node_ptr create( one_input_node_ptr &, agenda_ptr const&, action_ptr const&);
			static leaf_node_ptr create( two_input_node_ptr &, agenda_ptr const&, action_ptr const&);
			static leaf_node_ptr create( negative_node_ptr &, agenda_ptr const&, action_ptr const&);
		
			void activate( tuple_handle &);
		
			void detach();
		};
	}
};

#endif // OGX_RETE_LEAF_NODE_H
