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

#ifndef OT_ALGORITHM_HPP
#define OT_ALGORITHM_HPP

#include <algorithm>
#include <vector>

namespace ot
{

/*
	Function: all_of<I, P>

	(C++11) Checks if unary predicate p returns true for all elements in the range [first, last).
*/

template<typename I, class P>
inline bool all_of( I first, I last, P p )
{
	for ( ; first != last; ++first )
	{
		if ( !p( *first ) ) return false;
	}
	return true;
}

/*
	Function: any_of<I, P>

	(C++11) Checks if unary predicate p returns true for at least one element in the range [first, last).
*/

template<typename I, class P>
inline bool any_of( I first, I last, P p )
{
	for ( ; first != last; ++first )
	{
		if ( p( *first ) ) return true;
	}
	return false;
}

/*
	Function: none_of<I, P>

	(C++11) Checks if unary predicate p returns true for no elements in the range [first, last).
*/

template<typename I, class P>
inline bool none_of( I first, I last, P p )
{
	for ( ; first != last; ++first )
	{
		if ( p( *first ) ) return false;
	}
	return true;
}

/*
	Function: weakly_dominates<I, P>

	Checks if the first range [first1, last1) is less or equal than the
	second range [first2, last2).
*/

template<typename I1, typename I2>
inline bool weakly_dominates( I1 first1, I1 last1, I2 first2, I2 last2 )
{
	for ( ; ( first1 != last1 ) && ( first2 != last2 ); ++first1, ++first2 )
	{
		if ( *first2 < *first1 ) return false;
	}
	return true;
}

template<typename I1, typename I2, class P>
inline bool weakly_dominates( I1 first1, I1 last1, I2 first2, I2 last2, P p )
{
	for ( ; ( first1 != last1 ) && ( first2 != last2 ); ++first1, ++first2 )
	{
		if ( p( *first2, *first1 ) ) return false;
	}
	return true;
}

/*
	Function: dominates<I, P>

	Checks if the first range [first1, last1) is less or equal than the
	second range [first2, last2) with at least one strict inequality.
*/

template<typename I1, typename I2>
inline bool dominates( I1 first1, I1 last1, I2 first2, I2 last2 )
{
	bool result = false;
	for ( ; ( first1 != last1 ) && ( first2 != last2 ); ++first1, ++first2 )
	{
		if ( *first2 < *first1 ) return false;    // Same as weakly_dominates, but
		result = result || ( *first1 < *first2 ); // must have at least one strict inequality
	}
	return result;
}

template<typename I1, typename I2, class P>
inline bool dominates( I1 first1, I1 last1, I2 first2, I2 last2, P p )
{
	bool result = false;
	for ( ; ( first1 != last1 ) && ( first2 != last2 ); ++first1, ++first2 )
	{
		if ( p( *first2, *first1 ) ) return false;
		result = result || p( *first1, *first2 );
	}
	return result;
}

/*
	Function: strictly_dominates<I, P>

	Checks if the first range [first1, last1) is strictly less than the
	second range [first2, last2).
*/

template<typename I1, typename I2>
inline bool strictly_dominates( I1 first1, I1 last1, I2 first2, I2 last2 )
{
	for ( ; ( first1 != last1 ) && ( first2 != last2 ); ++first1, ++first2 )
	{
		if ( !( *first1 < *first2 ) ) return false;
	}
	return true;
}

template<typename I1, typename I2, class P>
inline bool strictly_dominates( I1 first1, I1 last1, I2 first2, I2 last2, P p )
{
	for ( ; ( first1 != last1 ) && ( first2 != last2 ); ++first1, ++first2 )
	{
		if ( !p( *first1, *first2 ) ) return false;
	}
	return true;
}

}

////////////////////////////////////////////////////////////////////////////////

namespace std
{

// Define swap for specific-case of std::vector<bool>.
inline void swap( vector<bool>::reference a, vector<bool>::reference b )
{
	bool c = a;
	a = b;
	b = c;
}

}

#endif

