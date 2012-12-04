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
#include "tuple_join_node.h"

#include <algorithm>

#include <boost/bind.hpp>

#include "tuple_node.h"
#include "one_input_node.h"

namespace ogx
{
	namespace rete
	{
		tuple_join_node::apply::apply( tuple_join_node & pn, tuple_handle const& th)
		:
		_pn( pn),
		_th( th)
		{}
		
		void 
		tuple_join_node::apply::operator()( argument_type arg)
		{
			tuple_handle th( tuple::create( arg, _th) );
			_pn.store( th);
			_pn._children( th);
		}
		
		tuple_join_node::tuple_join_node( tuple_node_ptr const& ltn_ptr, tuple_node_ptr const& rtn_ptr)
		:
		_children(),
		_cons(),
		_items(),
		_left_items( ltn_ptr->_items),
		_right_items( rtn_ptr->_items),
		_decls()
		{ 
			_decls.insert( ltn_ptr->_decl); 
			_decls.insert( rtn_ptr->_decl);
		}
		
		tuple_join_node::tuple_join_node( tuple_join_node_ptr const& tjn_ptr, tuple_node_ptr const& tn_ptr)
		:
		_children(),
		_cons(),
		_items(),
		_left_items( tjn_ptr->_items),
		_right_items( tn_ptr->_items),
		_decls( tjn_ptr->_decls)
		{ _decls.insert( tn_ptr->_decl); }
		
		tuple_join_node_ptr 
		tuple_join_node::create( tuple_node_ptr const& ltn_ptr, tuple_node_ptr const& rtn_ptr)
		{
			tuple_join_node_ptr __pn_ptr( new tuple_join_node( ltn_ptr, rtn_ptr) );
			ltn_ptr->left_attach( __pn_ptr);
			rtn_ptr->right_attach( __pn_ptr);
			return __pn_ptr;
		}
		
		tuple_join_node_ptr 
		tuple_join_node::create( tuple_join_node_ptr const& tjn_ptr, tuple_node_ptr const& tn_ptr)
		{
			tuple_join_node_ptr __pn_ptr( new tuple_join_node( tjn_ptr, tn_ptr) );
			tjn_ptr->attach( __pn_ptr);
			tn_ptr->right_attach( __pn_ptr);
			return __pn_ptr;
		}
		
		void 
		tuple_join_node::left_activate( tuple_handle & th)
		{
			std::list< tuple_handle > lst( _right_items() );
			std::for_each(
				lst.begin(),
				lst.end(),
				apply( * this, th) );
		}
		
		void 
		tuple_join_node::right_activate( tuple_handle & th)
		{
			std::list< tuple_handle > lst( _left_items() );
			std::for_each(
				lst.begin(),
				lst.end(),
				apply( * this, th) );
		}
		
		void 
		tuple_join_node::store( tuple_handle const& th)
		{ 
			th->_cons.push_back( 
				_items.connect(
					adaptor( th) ) ); 
		}
		
		void 
		tuple_join_node::attach( one_input_node_ptr const& oin_ptr)
		{ 
			oin_ptr->_cons.push_back(
				_children.connect( 
					boost::bind( 
						& one_input_node::activate, 
						oin_ptr, 
						_1) ) );  
		}
		
		void 
		tuple_join_node::attach( tuple_join_node_ptr const& tjn_ptr)
		{ 
			tjn_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& tuple_join_node::left_activate, 
						tjn_ptr, 
						_1) ) );  
		}
		
		void 
		tuple_join_node::detach()
		{ 
			std::for_each(
				_cons.begin(),
				_cons.end(),
				std::mem_fun_ref( 
					& boost::signals::connection::disconnect) ); 
		}
	}
};
