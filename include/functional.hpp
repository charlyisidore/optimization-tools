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

#ifndef OT_FUNCTIONAL_HPP
#define OT_FUNCTIONAL_HPP

// Definition of __ot_functional_decltype(T1,OP,T2) : returns the type of (T1 OP T2).
#if __cplusplus > 201100L || __GXX_EXPERIMENTAL_CXX0X__
#include <utility>
#define __ot_functional_decltype(T1,OP,T2) decltype( std::declval<T1>() OP std::declval<T2>() )
#elif __GNUC__
#define __ot_functional_decltype(T1,OP,T2) __typeof__( T1() OP T2() )
#else
#warning "Your compiler is not supported."
#endif

namespace ot
{

/*
	Class: identity<T>
*/

template<typename T>
struct identity
{
	typedef T first_argument_type;
	typedef T result_type;

	result_type operator() ( const first_argument_type & x ) const
	{
		return x;
	}
};

/*
	Class: plus<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct plus
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef __ot_functional_decltype( T1, +, T2 ) result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x + y;
	}
};

/*
	Class: minus<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct minus
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef __ot_functional_decltype( T1, -, T2 ) result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x - y;
	}
};

/*
	Class: negate<T>
*/

template<typename T>
struct negate
{
	typedef T first_argument_type;
	typedef T result_type;

	result_type operator() ( const first_argument_type & x ) const
	{
		return -x;
	}
};

/*
	Class: multiplies<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct multiplies
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef __ot_functional_decltype( T1, *, T2 ) result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x * y;
	}
};

/*
	Class: divides<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct divides
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef __ot_functional_decltype( T1, /, T2 ) result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x / y;
	}
};

/*
	Class: modulus<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct modulus
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef __ot_functional_decltype( T1, %, T2 ) result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x % y;
	}
};

/*
	Class: equal_to<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct equal_to
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x == y;
	}
};

/*
	Class: not_equal_to<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct not_equal_to
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x != y;
	}
};

/*
	Class: less<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct less
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x < y;
	}
};

/*
	Class: less_equal<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct less_equal
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x <= y;
	}
};

/*
	Class: greater<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct greater
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x > y;
	}
};

/*
	Class: greater_equal<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct greater_equal
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x >= y;
	}
};

/*
	Class: logical_and<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct logical_and
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x && y;
	}
};

/*
	Class: logical_not<T>
*/

template<typename T>
struct logical_not
{
	typedef T first_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x ) const
	{
		return !x;
	}
};

/*
	Class: logical_or<T1, T2>
*/

template<typename T1, typename T2 = T1>
struct logical_or
{
	typedef T1 first_argument_type;
	typedef T2 second_argument_type;
	typedef bool result_type;

	result_type operator() ( const first_argument_type & x, const second_argument_type & y ) const
	{
		return x || y;
	}
};

}

#endif
