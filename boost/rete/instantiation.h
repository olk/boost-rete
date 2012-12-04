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
#ifndef OGX_RETE_INSTANTIATION_H
#define OGX_RETE_INSTANTIATION_H

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

#include <ogx/rete/action.h>

namespace ogx
{
	namespace rete
	{
		class tuple;
		class agenda;
		class instantiation;
		
		typedef boost::shared_ptr< tuple >			tuple_handle;
		typedef boost::shared_ptr< instantiation >	instantiation_ptr;
		
		class instantiation
		{
		private:
			friend class agenda;
		
			tuple_handle 					_th;
			action_ptr						_act_ptr;
			boost::signals::connection		_con;
		
			instantiation( tuple_handle const&, action_ptr const&);
		
		public:
			static instantiation_ptr create( tuple_handle const&, action_ptr const&);
			
			void operator()();
		};
	}
};

#endif // OGX_RETE_INSTANTIATION_H
