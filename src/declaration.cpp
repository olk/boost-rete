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
#include "declaration.h"

namespace ogx
{
	namespace rete
	{
		declaration::declaration(	std::string const& header, 
									std::string const& vname, 
									std::string const& info)
		:
		_header( header),
		_vname( vname),
		_info( info)
		{}
		
		std::string const& 
		declaration::get_header() const
		{ return _header; }
		
		std::string const& 
		declaration::get_vname() const
		{ return _vname; }
		
		std::string const& 
		declaration::get_info() const
		{ return _info; }
		
		bool operator<( declaration const& decl1, declaration const& decl2)
		{ 
			std::string s1( decl1._header + decl1._vname + decl1._info);
			std::string s2( decl2._header + decl2._vname + decl2._info);
			return s1 < s2; 
		}
		
		bool operator>( declaration const& decl1, declaration const& decl2)
		{ 
			std::string s1( decl1._header + decl1._vname + decl1._info);
			std::string s2( decl2._header + decl2._vname + decl2._info);
			return s1 > s2;
		}
		
		bool operator==( declaration const& decl1, declaration const&decl2)
		{ 
			std::string s1( decl1._header + decl1._vname + decl1._info);
			std::string s2( decl2._header + decl2._vname + decl2._info);
			return s1 == s2; 
		}
		
		bool operator!=( declaration const& decl1, declaration const& decl2)
		{ return ! ( decl1 == decl2); }
	}
}
