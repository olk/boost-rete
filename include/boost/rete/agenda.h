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
#ifndef OGX_RETE_AGENDA_H
#define OGX_RETE_AGENDA_H

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

namespace ogx
{
	namespace rete
	{
		class tuple;
		class action;
		
		typedef boost::shared_ptr< tuple >		tuple_handle;
		typedef boost::shared_ptr< action >		action_ptr;
			
		class agenda
		{
		private:
			struct topmost_only
			{
				typedef void result_type;
			
				template< typename InputIterator >
				result_type operator()( InputIterator first, InputIterator last) const
				{ if ( first != last) * first; }
			};
			
			typedef boost::signal< void(), topmost_only >		cs_sig_type;
			
			cs_sig_type		_cs;
			
			void store( tuple_handle const&, action_ptr const&);
				
		public:
			void add( tuple_handle const&, action_ptr const&);	
			void fire();	
			bool empty() const;
			void clear();
		};
		
		typedef boost::shared_ptr< agenda >		agenda_ptr;
	}
};

#endif // OGX_RETE_AGENDA_H
