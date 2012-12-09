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
#ifndef OGX_RETE_ASSO_INSERT_ITERATOR_H
#define OGX_RETE_ASSO_INSERT_ITERATOR_H

#include <iterator>

namespace ogx
{
	namespace rete
	{
		template< typename Con >
		class asso_insert_iterator
		{
		protected:
			Con & _con;
		
		public:
			explicit asso_insert_iterator( Con & con) : _con( con) {}
			
			asso_insert_iterator &
			operator=( asso_insert_iterator const& rhs)
			{
				if ( this == & rhs) return * this;
				_con = rhs._con;
				return * this;
			}
			
			asso_insert_iterator &
			operator=( typename Con::value_type const& value)
			{
				_con.insert( value);
				return * this;
			}	
			
			asso_insert_iterator &
			operator*()
			{ return * this; }
			
			asso_insert_iterator &
			operator++()
			{ return * this; }
			
			asso_insert_iterator &
			operator++( int)
			{ return * this; }
		};
			
		template< typename Con >
		inline
		asso_insert_iterator< Con > asso_inserter( Con & con)
		{ return asso_insert_iterator< Con >( con); }
	}
}

#endif // OGX_RETE_ASSO_INSERT_ITERATOR_H
