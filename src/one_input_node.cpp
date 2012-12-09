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
#include "one_input_node.h"

#include <algorithm>

#include "tuple_node.h"
#include "tuple_join_node.h"
#include "alpha_memory.h"
#include "condition.h"

namespace ogx
{
	namespace rete
	{
		one_input_node::one_input_node( tuple_node_ptr const& tn_ptr, condition_ptr const& cond_ptr)
		:
		_am_ptr( alpha_memory::create( tn_ptr) ),
		_cons(),
		_cond_ptr( cond_ptr)
		{}
		
		one_input_node::one_input_node( tuple_join_node_ptr const& tjn_ptr, condition_ptr const& cond_ptr)
		:
		_am_ptr( alpha_memory::create( tjn_ptr) ),
		_cons(),
		_cond_ptr( cond_ptr)
		{}
		
		one_input_node_ptr 
		one_input_node::create( tuple_node_ptr const& tn_ptr, condition_ptr const& cond_ptr)
		{ 
			one_input_node_ptr oin_ptr( new one_input_node( tn_ptr, cond_ptr) );
			tn_ptr->attach( oin_ptr);
			return oin_ptr;
		}
		
		one_input_node_ptr 
		one_input_node::create( tuple_join_node_ptr const& tjn_ptr, condition_ptr const& cond_ptr)
		{ 
			one_input_node_ptr oin_ptr( new one_input_node( tjn_ptr, cond_ptr) );
			tjn_ptr->attach( oin_ptr);
			return oin_ptr;
		}
		
		bool 
		one_input_node::eval( tuple_handle const& th) const
		{ return ( * _cond_ptr)( th); }
		
		void  
		one_input_node::activate( tuple_handle & th)
		{ if ( eval( th) ) _am_ptr->activate( th); }
		
		void 
		one_input_node::detach()
		{ 
			std::for_each(
				_cons.begin(),
				_cons.end(),
				std::mem_fun_ref( 
					& boost::signals::connection::disconnect) );
		}
	}
};
