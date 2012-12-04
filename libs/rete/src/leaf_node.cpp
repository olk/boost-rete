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
#include "leaf_node.h"

#include <algorithm>

#include "agenda.h"
#include "alpha_memory.h"
#include "one_input_node.h"
#include "two_input_node.h"
#include "negative_node.h"

namespace ogx
{
	namespace rete
	{
		leaf_node::leaf_node( agenda_ptr const& ag_ptr, action_ptr const& act_ptr)
		:
		_cons(),
		_ag_ptr( ag_ptr),
		_act_ptr( act_ptr)
		{}
		
		leaf_node_ptr
		leaf_node::create( one_input_node_ptr & oin_ptr, agenda_ptr const& ag_ptr, action_ptr const& act_ptr)
		{
			leaf_node_ptr ln_ptr( new leaf_node( ag_ptr, act_ptr) );
			oin_ptr->_am_ptr->attach( ln_ptr);
			return ln_ptr;
		}
		
		leaf_node_ptr
		leaf_node::create( two_input_node_ptr & tin_ptr, agenda_ptr const& ag_ptr, action_ptr const& act_ptr)
		{
			leaf_node_ptr ln_ptr( new leaf_node( ag_ptr, act_ptr) );
			tin_ptr->attach( ln_ptr);
			return ln_ptr;
		}
		
		leaf_node_ptr
		leaf_node::create( negative_node_ptr & nn_ptr, agenda_ptr const& ag_ptr, action_ptr const& act_ptr)
		{
			leaf_node_ptr ln_ptr( new leaf_node( ag_ptr, act_ptr) );
			nn_ptr->attach( ln_ptr);
			return ln_ptr;
		}
		
		void 
		leaf_node::activate( tuple_handle & th)
		{ _ag_ptr->add( th, _act_ptr); }
		
		void 
		leaf_node::detach()
		{ 
			std::for_each(
				_cons.begin(),
				_cons.end(),
				std::mem_fun_ref( 
					& boost::signals::connection::disconnect) ); 
		}
	}
};
