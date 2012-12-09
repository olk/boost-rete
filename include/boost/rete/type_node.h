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
#ifndef OGX_RETE_TYPE_NODE_H
#define OGX_RETE_TYPE_NODE_H

#include <list>
#include <typeinfo>

#include <boost/shared_ptr.hpp>
#include <boost/signal.hpp>

namespace ogx
{
	namespace rete
	{
		class fact;
		class tuple_node;
		class root_node;
		class type_node;
		
		typedef boost::shared_ptr< fact >			fact_handle;
		typedef boost::shared_ptr< tuple_node >		tuple_node_ptr;
		typedef boost::shared_ptr< root_node >		root_node_ptr;
		typedef boost::shared_ptr< type_node >		type_node_ptr;
		
		class type_node
		{
		private:
			typedef boost::signal< void ( fact_handle &) >	children_func_type;
			
			friend class root_node;
		
			children_func_type							_children;
			std::list< boost::signals::connection >		_cons;
			std::string									_info;
		
			type_node( std::string const&);
		
			bool instance_of( fact_handle const&) const;
		
		public:
			static type_node_ptr create( root_node_ptr const&, std::string const&);
			
			void activate( fact_handle &);	
			
			void attach( tuple_node_ptr const&);
			void detach();
		};
	}
};

#endif // OGX_RETE_TYPE_NODE_H
