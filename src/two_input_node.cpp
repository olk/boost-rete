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
#include "two_input_node.h"

#include <algorithm>

#include <boost/bind.hpp>

#include "tuple.h"
#include "alpha_memory.h"
#include "beta_memory.h"
#include "leaf_node.h"
#include "one_input_node.h"
#include "asso_insert_iterator.h"

namespace ogx
{
	namespace rete
	{
		two_input_node::apply::apply( two_input_node const& tin, tuple_handle const& rth)
		:
		_tin( tin),
		_rth( rth)
		{}
		
		void
		two_input_node::apply::operator()( tuple_handle const& lth)
		{
			if ( _tin._decls_shared.empty() )
			{
				tuple_handle th( tuple::create( lth, _rth) );
				_tin._children( th);
			}
			else
			{
				if ( _tin.test( lth, _rth) )
				{
					tuple_handle th( tuple::create( lth, _rth) );
					_tin._children( th);
				}
			}
		}
		
		two_input_node::two_input_node( one_input_node_ptr const& oin_ptr)
		:
		_children(),
		_cons(),
		_decls( oin_ptr->_am_ptr->_decls),
		_decls_shared(),
		_am_ptr( oin_ptr->_am_ptr),
		_bm_ptr()
		{}
		
		two_input_node::two_input_node( beta_memory_ptr const& bm_ptr, one_input_node_ptr const& oin_ptr)
		:
		_children(),
		_cons(),
		_decls(),
		_decls_shared(),
		_am_ptr( oin_ptr->_am_ptr),
		_bm_ptr( bm_ptr)
		{
			std::merge(
				bm_ptr->_decls.begin(),
				bm_ptr->_decls.end(),
				oin_ptr->_am_ptr->_decls.begin(),
				oin_ptr->_am_ptr->_decls.end(),
				asso_inserter( _decls) );
			std::set_intersection(
				bm_ptr->_decls.begin(),
				bm_ptr->_decls.end(),
				oin_ptr->_am_ptr->_decls.begin(),
				oin_ptr->_am_ptr->_decls.end(),
				asso_inserter( _decls_shared) );	
		}
		
		two_input_node_ptr 
		two_input_node::create( one_input_node_ptr const& oin_ptr)
		{ 
			two_input_node_ptr tin_ptr( new two_input_node( oin_ptr) ); 
			oin_ptr->_am_ptr->attach( tin_ptr);
			return tin_ptr;
		}
		
		two_input_node_ptr 
		two_input_node::create( beta_memory_ptr const& bm_ptr, one_input_node_ptr const& oin_ptr)
		{ 
			two_input_node_ptr tin_ptr( new two_input_node( bm_ptr, oin_ptr) ); 
			bm_ptr->attach( tin_ptr);
			oin_ptr->_am_ptr->attach( tin_ptr);
			return tin_ptr;
		}
		
		bool
		two_input_node::test( tuple_handle const& lth, tuple_handle const& rth) const
		{
			std::set< declaration >::const_iterator i( _decls_shared.begin() );
			std::set< declaration >::const_iterator e( _decls_shared.end() );
								
			while ( i != e)
			{
				tuple::iterator li( lth->find( * i) );
				tuple::iterator ri( rth->find( * i) );
		
				bool bl = li == lth->end();
				bool br = ri == rth->end();
				if ( li == lth->end() || 
					ri == rth->end() ||
					( * li) != ( * ri) )
					return false;
				++i;
			}
		
			return true;
		}
			
		void  
		two_input_node::left_activate( tuple_handle & lth)
		{
			std::list< tuple_handle > lst( _am_ptr->_items() );
			std::for_each(
				lst.begin(),
				lst.end(),
				apply( * this, lth) );
		}
		
		void  
		two_input_node::right_activate( tuple_handle & rth)
		{
			if( ! _bm_ptr)
				_children( rth);
			else
			{
				std::list< tuple_handle > lst( _bm_ptr->_items() );
				std::for_each(
					lst.begin(),
					lst.end(),
					apply( * this, rth) );
			}
		}
		
		void 
		two_input_node::attach( leaf_node_ptr const& ln_ptr)
		{ 
			ln_ptr->_cons.push_back( 
				_children.connect( 
					boost::bind( 
						& leaf_node::activate, 
						ln_ptr, 
						_1) ) );   
		}
		
		void 
		two_input_node::attach( beta_memory_ptr const& bm_ptr)
		{ 
			bm_ptr->_cons.push_back( 
					_children.connect( 
						boost::bind( 
							& beta_memory::activate, 
							bm_ptr, 
							_1) ) );  
		}
		
		void 
		two_input_node::detach()
		{ 
			std::for_each(
				_cons.begin(),
				_cons.end(),
				std::mem_fun_ref( 
					& boost::signals::connection::disconnect) ); 
		}
	}
};
