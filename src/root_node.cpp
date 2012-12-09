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
#include "root_node.h"

#include <boost/bind.hpp>

#include "type_node.h"

namespace ogx
{
	namespace rete
	{
		root_node::root_node()
		:
		_children()
		{}
		
		root_node_ptr 
		root_node::create()
		{ return root_node_ptr( new root_node() ); }
		
		void
		root_node::activate( fact_handle & fh)
		{ _children( fh); }
		
		void 
		root_node::attach( type_node_ptr const& tn_ptr)
		{ 
			tn_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& type_node::activate, 
						tn_ptr, 
						_1) ) ); 
		}
		
		void
		root_node::clear()
		{ _children.disconnect_all_slots(); };
	}
}
