/*
	Copyright (c) 2012 Charly LERSTEAU

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef OT_UTILITY_HPP
#define OT_UTILITY_HPP

#include <utility>

template<typename T, class A>
std::ostream & operator << ( std::ostream & os, const std::vector<T, A> & x )
{
	if ( !x.empty() )
	{
		typename std::vector<T, A>::const_iterator it( x.begin() );
		os << *it;
		for ( ++it; it != x.end(); ++it )
		{
			os << ' ' << *it;
		}
	}
	return os;
}

template<typename T>
std::ostream & operator << ( std::ostream & os, const std::valarray<T> & x )
{
	if ( x.size() > 0 )
	{
		os << x[0];
		for ( std::size_t i = 1; i < x.size(); ++i )
		{
			os << ' ' << x[i];
		}
	}
	return os;
}

#endif

