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
#include "alpha_memory.h"

#include <algorithm>

#include <boost/bind.hpp>

#include "two_input_node.h"
#include "tuple_node.h"
#include "tuple_join_node.h"
#include "leaf_node.h"
#include "negative_node.h"

namespace ogx
{
	namespace rete
	{
		alpha_memory::alpha_memory( tuple_node_ptr const& tn_ptr)
		:
		_children(),
		_items(),
		_decls()
		{ _decls.insert( tn_ptr->_decl); }
		
		alpha_memory::alpha_memory( tuple_join_node_ptr const& tjn_ptr)
		:
		_children(),
		_items(),
		_decls( tjn_ptr->_decls)
		{}
		
		alpha_memory_ptr
		alpha_memory::create( tuple_node_ptr const& tn_ptr)
		{ return alpha_memory_ptr( new alpha_memory( tn_ptr) ); }
		
		alpha_memory_ptr
		alpha_memory::create( tuple_join_node_ptr const& tjn_ptr)
		{ return alpha_memory_ptr( new alpha_memory( tjn_ptr) ); }
		
		void 
		alpha_memory::activate( tuple_handle & th)
		{ 
			store( th); 
			_children( th);
		}
			
		void 
		alpha_memory::store( tuple_handle const& th)
		{ 
			th->_cons.push_back( 
				_items.connect( 
					adaptor( th) ) ); 
		}
		
		void
		alpha_memory::attach( leaf_node_ptr const& ln_ptr)
		{ 
			ln_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& leaf_node::activate, 
						ln_ptr, 
						_1) ) );  
		}
		
		void
		alpha_memory::attach( two_input_node_ptr const& tin_ptr)
		{ 
			tin_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& two_input_node::right_activate, 
						tin_ptr, 
						_1) ) );  
		}
		
		void
		alpha_memory::attach( negative_node_ptr const& nn_ptr)
		{ 
			nn_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& negative_node::right_activate, 
						nn_ptr, 
						_1) ) );  
		}
	}
};
