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
#ifndef OGX_RETE_ROOT_NODE_H
#define OGX_RETE_ROOT_NODE_H

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

namespace ogx
{
	namespace rete
	{
		class fact;
		class type_node;
		class root_node;
		
		typedef boost::shared_ptr< fact >		fact_handle;
		typedef boost::shared_ptr< type_node >	type_node_ptr;
		typedef boost::shared_ptr< root_node >	root_node_ptr;
		
		class root_node
		{
		private:
			typedef boost::signal< void ( fact_handle &) >	children_sig_type;
		
			children_sig_type		_children;
			
			root_node();
		
		public:
			static root_node_ptr create();
		
			void activate( fact_handle &);
		
			void attach( type_node_ptr const&);
		
			void clear();
		};
	}
};

#endif // OGX_RETE_ROOT_NODE_H
