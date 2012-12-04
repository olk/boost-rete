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
#ifndef OGX_RETE_MEMORY_H
#define OGX_RETE_MEMORY_H

#include <boost/shared_ptr.hpp>

#include <ogx/rete/agenda.h>
#include <ogx/rete/imemory.h>
#include <ogx/rete/root_node.h>

namespace ogx
{
	namespace rete
	{
		class fact;
		
		typedef boost::shared_ptr< fact >	fact_handle;
		
		template< typename Agenda >
		class memory 
		: 
		public imemory
		{
		private:
			typedef boost::shared_ptr< Agenda > agenda_ptr;	    
				
			agenda_ptr		_ag_ptr;
			root_node_ptr	_rn_ptr;	
		
		public:
			memory( agenda_ptr const& ag_ptr, root_node_ptr const& rn_ptr)
			: 
			imemory(),
			_ag_ptr( ag_ptr),
			_rn_ptr( rn_ptr)    
			{}
		
			~memory() {}
		
			void clear()
			{ 
				_rn_ptr->clear();
				_ag_ptr->clear(); 
			}
		
			void add( fact_handle fh)
			{ _rn_ptr->activate( fh); }
		
			void modify( fact_handle fh)
			{
				remove( fh);
				add( fh);
			}
		
			void remove( fact_handle fh)
			{ fh->remove(); }
		
			void run()
			{ _ag_ptr->fire(); }
		};
	}
}

#endif // OGX_RETE_MEMORY_H
