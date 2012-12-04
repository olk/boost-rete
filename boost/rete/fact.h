/***************************************************************************
 *   Copyright (C) 2004 by itkowa                                          *
 *   itkowa@ITDD02                                                         *
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
#ifndef OGX_RETE_FACT_H
#define OGX_RETE_FACT_H

#include <list>
#include <typeinfo>

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>
#include <boost/any.hpp>
#include <boost/bind.hpp>

#include <ogx/rete/tuple.h>

namespace ogx
{
	namespace
	{
		class fact;
		
		template< typename T >
		T & fact_cast( fact &);
		
		class fact
		{
		private:
			typedef boost::signal< void() >		tuple_sig_type;
		
			friend class tuple;
			friend class tuple::apply;
			template< typename T >
			friend T & fact_cast( fact &);
		
			boost::any		_any;
			tuple_sig_type	_tp_sig;
			
			void add( tuple_handle const& th)
			{ _tp_sig.connect( boost::bind( & tuple::detach, th) ); }
		
		public:
			template< typename T >
			fact( T const& t) 
			: 
			_any( t),
			_tp_sig()
			{}
				
			const std::type_info & type() const
			{ return _any.type(); }
			
			void remove()
			{ _tp_sig(); }
		};
		
		typedef boost::shared_ptr< fact >	fact_handle;
		
		template< typename T >
		T & fact_cast( fact & f)
		{ return * boost::any_cast< T >( & f._any); }
		
		template< typename T >
		T & fact_cast( fact_handle & fh)
		{ return fact_cast< T >( * fh); }
	}
}

#endif // OGX_RETE_FACT_H
