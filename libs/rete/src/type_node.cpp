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
#include "type_node.h"

#include <algorithm>

#include <boost/bind.hpp>

#include "fact.h"
#include "root_node.h"
#include "tuple_node.h"

namespace ogx
{
	namespace rete
	{
		type_node::type_node( std::string const& info)
		:
		_children(),
		_cons(),
		_info( info)
		{}
		
		type_node_ptr 
		type_node::create( root_node_ptr const& rn_ptr, std::string const& info)
		{ 
			type_node_ptr tn_ptr( new type_node( info) ); 
			rn_ptr->attach( tn_ptr);
			return tn_ptr;
		}
		
		bool 
		type_node::instance_of( fact_handle const& fh) const
		{ return std::string( fh->type().name() ).find( _info) != std::string::npos; }
		
		void
		type_node::activate( fact_handle & fh)
		{ if ( instance_of( fh) ) _children( fh); }
		
		void 
		type_node::attach( tuple_node_ptr const& tn_ptr)
		{ 
			tn_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& tuple_node::activate, 
						tn_ptr, 
						_1) ) ); 
		}
		
		void 
		type_node::detach()
		{ 
			std::for_each(
				_cons.begin(),
				_cons.end(),
				std::mem_fun_ref( 
					& boost::signals::connection::disconnect) );
		}
	}
}
