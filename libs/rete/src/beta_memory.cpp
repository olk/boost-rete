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
#include "beta_memory.h"

#include <algorithm>

#include <boost/bind.hpp>

#include "two_input_node.h"
#include "negative_node.h"

namespace ogx
{
	namespace rete
	{
		beta_memory::beta_memory( two_input_node_ptr const& tin_ptr)
		:
		_children(),
		_cons(),
		_items(),
		_decls( tin_ptr->_decls)
		{}
		
		beta_memory::beta_memory( negative_node_ptr const& nn_ptr)
		:
		_children(),
		_cons(),
		_items(),
		_decls( nn_ptr->_decls)
		{}
		
		beta_memory_ptr 
		beta_memory::create( two_input_node_ptr const& tin_ptr)
		{
			beta_memory_ptr bm_ptr( new beta_memory( tin_ptr) );
			tin_ptr->attach( bm_ptr);
			return bm_ptr;
		}
		
		beta_memory_ptr 
		beta_memory::create( negative_node_ptr const& nn_ptr)
		{
			beta_memory_ptr bm_ptr( new beta_memory( nn_ptr) );
			nn_ptr->attach( bm_ptr);
			return bm_ptr;
		}
		
		void 
		beta_memory::activate( tuple_handle & th)
		{ 
			store( th); 
			_children( th);
		}
		
		void 
		beta_memory::store( tuple_handle & th)
		{ 
			th->_cons.push_back( 
				_items.connect(
					adaptor( th) ) ); 
		}
		
		void 
		beta_memory::attach( two_input_node_ptr const& tin_ptr)
		{ 
			tin_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& two_input_node::left_activate, 
						tin_ptr, 
						_1) ) );  
		}
		
		void 
		beta_memory::attach( negative_node_ptr const& nn_ptr)
		{ 
			nn_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& negative_node::left_activate, 
						nn_ptr, 
						_1) ) );  
		}
		
		void 
		beta_memory::detach()
		{ 
			std::for_each(
				_cons.begin(),
				_cons.end(),
				std::mem_fun_ref( 
					& boost::signals::connection::disconnect) ); 
		}
	}
};
