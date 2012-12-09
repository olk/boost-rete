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
#include "tuple.h"

#include <stdexcept>
#include <algorithm>
#include <string>
#include <utility>

#include "asso_insert_iterator.h"
#include "fact.h"

namespace ogx
{
	namespace rete
	{
		std::size_t
		tuple::sdbm::operator()( declaration const& decl) const
		{
			std::size_t hash = 0;
			int c;
			char const* s = std::string( decl.get_info() + "-" + decl.get_vname() ).c_str();
				
			while ( c = * s++)
				hash = c + ( hash << 6) + ( hash << 16) - hash;
			
			return hash;
		}
		
		tuple::apply::apply( tuple_handle const& th) : _th( th) {}
		
		void
		tuple::apply::operator()( argument_type arg)
		{ arg.second.second->add( _th); }
		
		tuple::tuple( declaration const& decl, fact_handle const& fh)
		:
		_map(),
		_cons()
		{
			_map.insert( 
				map_type::value_type( 
					std::make_pair( 
						decl, 
						std::make_pair( 
							decl, 
							fh) ) ) );
		}
			
		tuple::tuple( tuple const& ltp, tuple const& rtp)
		:
		_map( ltp._map.size() > rtp._map.size() ? ltp._map : rtp._map),
		_cons()
		{
			if ( ltp._map.size() > rtp._map.size() )
			{
				std::copy( 
					rtp._map.begin(), 
					rtp._map.end(), 
					asso_inserter( _map) );
			}
			else
			{
				std::copy( 
					ltp._map.begin(), 
					ltp._map.end(), 
					asso_inserter( _map) );
			}
		}
		
		tuple::tuple( tuple const& tp)
		:
		_map( tp._map),
		_cons()
		{}
		
		tuple_handle 
		tuple::create( declaration const& decl, fact_handle const& fh)
		{ 
			tuple_handle th( new tuple( decl, fh) ); 
			fh->add( th);
			return th;
		}
		
		tuple_handle 
		tuple::create( tuple_handle const& lth, tuple_handle const& rth)
		{ 
			tuple_handle th( new tuple( * lth, * rth) ); 
			std::for_each(
				th->_map.begin(),
				th->_map.end(),
				apply( th) );
			return th;
		}
		
		tuple_handle 
		tuple::create( tuple const& ltp, tuple const& rtp)
		{ 
			tuple_handle th( new tuple( ltp, rtp) ); 
			std::for_each(
				th->_map.begin(),
				th->_map.end(),
				apply( th) );
			return th;
		}
		
		tuple_handle 
		tuple::create( tuple_handle const& th)
		{ return tuple_handle( new tuple( * th) ); }
		
		tuple::iterator
		tuple::find( declaration const& decl)
		{ return _map.find( decl); }
		
		tuple::iterator 
		tuple::begin()
		{ return _map.begin(); }
		
		tuple::iterator 
		tuple::end()
		{ return _map.end(); }
			
		void
		tuple::detach()
		{
			std::for_each(
				_cons.begin(),
				_cons.end(),
				std::mem_fun_ref( 
					& boost::signals::connection::disconnect) );
		}
		
		adaptor::adaptor( tuple_handle const& th) : _th( th) {}
		
		tuple_handle
		adaptor::operator()() const
		{ return _th; }
	}
}
