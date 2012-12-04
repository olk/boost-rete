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
#include "loader.h"

#include <stdexcept>
#include <fstream>

#include <boost/spirit/iterator/file_iterator.hpp>

namespace ogx
{
	namespace rete
	{
		loader::loader( std::string const & filename)
		:
		_filename( filename)
		{}
		
		inline
		loader::result_type
		loader::operator()()
		{
			boost::spirit::file_iterator<> first( _filename);
	
			if ( ! first)
				throw std::runtime_error("failure by open the file '" + _filename + "'");
	
			boost::spirit::file_iterator<> last = first.make_end();
			
			return std::string( first, last);
		}
	}
}
