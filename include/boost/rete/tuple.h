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
#ifndef	OGX_RETE_TUPLE_H
#define	OGX_RETE_TUPLE_H

#include <functional>
#include <list>

#include <ext/hash_map>

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <ogx/rete/declaration.h>

namespace ogx
{
	namespace rete
	{
		class agenda;
		class fact;
		class tuple;
		class tuple_node;
		class tuple_join_node;
		class negative_node;
		class alpha_memory;
		class beta_memory;
		
		typedef boost::shared_ptr< fact >	fact_handle;
		typedef boost::shared_ptr< tuple >	tuple_handle;
		
		class tuple
		{
		private:
			struct sdbm
			:
			public std::unary_function< declaration const&, std::size_t >
			{
				std::size_t operator()( declaration const&) const;
			};
	
		public:
			typedef __gnu_cxx::hash_map< declaration, std::pair< declaration, fact_handle >, sdbm >		map_type;
			typedef map_type::iterator																	iterator;
	
		private:
			friend class agenda;
			friend class tuple_node;
			friend class tuple_join_node;
			friend class negative_node;
			friend class alpha_memory;
			friend class beta_memory;
			
			map_type									_map;
			std::list< boost::signals::connection >		_cons;
			
			tuple( declaration const&, fact_handle const&);
			tuple( tuple const&, tuple const&);
			tuple( tuple const&);
					
		public:	
			class apply
			:
			public std::unary_function< map_type::value_type const&, void >
			{
			private:
				tuple_handle const&	_th;
				
			public:
				apply( tuple_handle const&);
				
				void operator()( argument_type);
			};  
				
			static tuple_handle create( declaration const&, fact_handle const&);
			static tuple_handle create( tuple_handle const&);
			static tuple_handle create( tuple_handle const&, tuple_handle const&);
			static tuple_handle create( tuple const&, tuple const&);
				
			iterator find( declaration const&);
			iterator begin();
			iterator end();
		
			void detach();
		};
		
		template< typename Container >
		struct aggregate_values
		{
			typedef Container result_type;
		
			template< typename InputIterator >
			Container operator()( InputIterator first, InputIterator last) const
			{ return Container( first, last); }
		};	
		
		class adaptor
		{
		private:
			tuple_handle	_th;
	
		public:
			adaptor( tuple_handle const&);
	
			tuple_handle operator()() const;
		};
	}
}

#endif // OGX_RETE_TUPLE_H
