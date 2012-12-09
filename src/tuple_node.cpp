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
#include "tuple_node.h"

#include <algorithm>

#include <boost/bind.hpp>

#include "tuple.h"
#include "type_node.h"
#include "tuple_join_node.h"
#include "one_input_node.h"

namespace ogx
{
	namespace rete
	{
		tuple_node::tuple_node( declaration const& decl)
		:
		_children(),
		_cons(),
		_items(),
		_decl( decl)
		{}
		
		tuple_node_ptr
		tuple_node::create( type_node_ptr const& tn_ptr, declaration const& decl)
		{
			tuple_node_ptr _tn_ptr( new tuple_node( decl) );
			tn_ptr->attach( _tn_ptr); 
			return _tn_ptr;
		}
		
		void 
		tuple_node::activate( fact_handle & fh)
		{ 
			tuple_handle th( tuple::create( _decl, fh) );
			store( th);
			_children( th); 
		}   
		
		void 
		tuple_node::store( tuple_handle const& th)
		{	
			th->_cons.push_back( 
				_items.connect(
					adaptor( th) ) ); 
		}
		
		void 
		tuple_node::left_attach( tuple_join_node_ptr const& tjn_ptr)
		{ 
			tjn_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& tuple_join_node::left_activate, 
						tjn_ptr, 
						_1) ) );  
		}
		
		void 
		tuple_node::right_attach( tuple_join_node_ptr const& tjn_ptr)
		{ 
			tjn_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& tuple_join_node::right_activate, 
						tjn_ptr, 
						_1) ) );  
		}
		
		void 
		tuple_node::attach( one_input_node_ptr const& oin_ptr)
		{ 
			oin_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& one_input_node::activate, 
						oin_ptr, 
						_1) ) );  
		}
		
		void 
		tuple_node::detach()
		{ 
			std::for_each(
				_cons.begin(),
				_cons.end(),
				std::mem_fun_ref( 
					& boost::signals::connection::disconnect) ); 
		}
	}
}




