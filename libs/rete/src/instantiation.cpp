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
#include "instantiation.h"

namespace ogx
{
	namespace rete
	{
		instantiation::instantiation( tuple_handle const& th, action_ptr const& act_ptr)
		:
		_th( th),
		_act_ptr( act_ptr),
		_con()
		{}
		
		instantiation_ptr
		instantiation::create( tuple_handle const& th, action_ptr const& act_ptr)
		{ return instantiation_ptr( new instantiation( th, act_ptr) ); }
		
		void 
		instantiation::operator()()
		{ 
			_con.disconnect();
			( * _act_ptr)( _th); 
		}
	}
};
