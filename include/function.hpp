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

#ifndef OT_FUNCTION_HPP
#define OT_FUNCTION_HPP

#include <iostream>
#include <typeinfo>

namespace ot
{

/*
	Class: function<R, T1, ..., AN>
	A callable function container.
*/

template<typename R, typename T1 = void, typename T2 = void, typename T3 = void, typename T4 = void>
class function
{
public:
	typedef R (*function_type)(T1, T2, T3, T4);
	typedef R (*callback_type)(void *, T1, T2, T3, T4);

	function() : _object( 0 ), _callback(), _static() {}
	function( function_type f ) : _object( 0 ), _callback(), _static( f ) {}
	template<class C>
	function( C * object ) : _object( object ), _callback( &method_callback<C, &C::operator()> ), _static() {}

	R operator () ( T1 a1, T2 a2, T3 a3, T4 a4 ) const
	{
		return _static ? _static( a1, a2, a3, a4 ) : (*_callback)( _object, a1, a2, a3, a4 );
	}

	template<class C, R (C::*Method)(T1, T2, T3, T4)>
	static function from_method( C * object )
	{
		return function( object, &method_callback<C, Method> );
	}

	template<class C, R (C::*Method)(T1, T2, T3, T4) const>
	static function from_method( C * object )
	{
		return function( object, &method_callback_const<C, Method> );
	}

	function & operator = ( const function & f )
	{
		_object   = f._object;
		_callback = f._callback;
		_static   = f._static;
		return *this;
	}

private:
	template<class C>
	function( C * object, callback_type callback ) : _object( object ), _callback( callback ), _static() {}

	template <class C, R (C::*Method)(T1, T2, T3, T4)>
	static R method_callback( void * object, T1 a1, T2 a2, T3 a3, T4 a4 )
	{
		return ( static_cast<C *>( object ) ->*Method )( a1, a2, a3, a4 );
	}

	template <class C, R (C::*Method)(T1, T2, T3, T4) const>
	static R method_callback_const( void * object, T1 a1, T2 a2, T3 a3, T4 a4 )
	{
		return ( static_cast<C *>( object ) ->*Method )( a1, a2, a3, a4 );
	}

	void          * _object;
	callback_type   _callback;
	function_type   _static;
};

////////////////////////////////////////////////////////////////////////////////

template<typename R, typename T1, typename T2, typename T3>
class function<R, T1, T2, T3, void>
{
public:
	typedef R (*function_type)(T1, T2, T3);
	typedef R (*callback_type)(void *, T1, T2, T3);

	function() : _object( 0 ), _callback(), _static() {}
	function( function_type f ) : _object( 0 ), _callback(), _static( f ) {}
	template<class C>
	function( C * object ) : _object( object ), _callback( &method_callback<C, &C::operator()> ), _static() {}

	R operator () ( T1 a1, T2 a2, T3 a3 ) const
	{
		return _static ? _static( a1, a2, a3 ) : (*_callback)( _object, a1, a2, a3 );
	}

	template<class C, R (C::*Method)(T1, T2, T3)>
	static function from_method( C * object )
	{
		return function( object, &method_callback<C, Method> );
	}

	template<class C, R (C::*Method)(T1, T2, T3) const>
	static function from_method( C * object )
	{
		return function( object, &method_callback_const<C, Method> );
	}

	function & operator = ( const function & f )
	{
		_object   = f._object;
		_callback = f._callback;
		_static   = f._static;
		return *this;
	}

private:
	template<class C>
	function( C * object, callback_type callback ) : _object( object ), _callback( callback ), _static() {}

	template <class C, R (C::*Method)(T1, T2, T3)>
	static R method_callback( void * object, T1 a1, T2 a2, T3 a3 )
	{
		return ( static_cast<C *>( object ) ->*Method )( a1, a2, a3 );
	}

	template <class C, R (C::*Method)(T1, T2, T3) const>
	static R method_callback_const( void * object, T1 a1, T2 a2, T3 a3 )
	{
		return ( static_cast<C *>( object ) ->*Method )( a1, a2, a3 );
	}

	void          * _object;
	callback_type   _callback;
	function_type   _static;
};

////////////////////////////////////////////////////////////////////////////////

template<typename R, typename T1, typename T2>
class function<R, T1, T2, void, void>
{
public:
	typedef R (*function_type)(T1, T2);
	typedef R (*callback_type)(void *, T1, T2);

	function() : _object( 0 ), _callback(), _static() {}
	function( function_type f ) : _object( 0 ), _callback(), _static( f ) {}
	template<class C>
	function( C * object ) : _object( object ), _callback( &method_callback<C, &C::operator()> ), _static() {}

	R operator () ( T1 a1, T2 a2 ) const
	{
		return _static ? _static( a1, a2 ) : (*_callback)( _object, a1, a2 );
	}

	template<class C, R (C::*Method)(T1, T2)>
	static function from_method( C * object )
	{
		return function( object, &method_callback<C, Method> );
	}

	template<class C, R (C::*Method)(T1, T2) const>
	static function from_method( C * object )
	{
		return function( object, &method_callback_const<C, Method> );
	}

	function & operator = ( const function & f )
	{
		_object   = f._object;
		_callback = f._callback;
		_static   = f._static;
		return *this;
	}

private:
	template<class C>
	function( C * object, callback_type callback ) : _object( object ), _callback( callback ), _static() {}

	template <class C, R (C::*Method)(T1, T2)>
	static R method_callback( void * object, T1 a1, T2 a2 )
	{
		return ( static_cast<C *>( object ) ->*Method )( a1, a2 );
	}

	template <class C, R (C::*Method)(T1, T2) const>
	static R method_callback_const( void * object, T1 a1, T2 a2 )
	{
		return ( static_cast<C *>( object ) ->*Method )( a1, a2 );
	}

	void          * _object;
	callback_type   _callback;
	function_type   _static;
};

////////////////////////////////////////////////////////////////////////////////

template<typename R, typename T1>
class function<R, T1, void, void, void>
{
public:
	typedef R (*function_type)(T1);
	typedef R (*callback_type)(void *, T1);

	function() : _object( 0 ), _callback(), _static() {}
	function( function_type f ) : _object( 0 ), _callback(), _static( f ) {}
	template<class C>
	function( C * object ) : _object( object ), _callback( &method_callback<C, &C::operator()> ), _static() {}

	R operator () ( T1 a1 ) const
	{
		return _static ? _static( a1 ) : (*_callback)( _object, a1 );
	}

	template<class C, R (C::*Method)(T1)>
	static function from_method( C * object )
	{
		return function( object, &method_callback<C, Method> );
	}

	template<class C, R (C::*Method)(T1) const>
	static function from_method( C * object )
	{
		return function( object, &method_callback_const<C, Method> );
	}

	function & operator = ( const function & f )
	{
		_object   = f._object;
		_callback = f._callback;
		_static   = f._static;
		return *this;
	}

private:
	template<class C>
	function( C * object, callback_type callback ) : _object( object ), _callback( callback ), _static() {}

	template <class C, R (C::*Method)(T1)>
	static R method_callback( void * object, T1 a1 )
	{
		return ( static_cast<C *>( object ) ->*Method )( a1 );
	}

	template <class C, R (C::*Method)(T1) const>
	static R method_callback_const( void * object, T1 a1 )
	{
		return ( static_cast<C *>( object ) ->*Method )( a1 );
	}

	void          * _object;
	callback_type   _callback;
	function_type   _static;
};

////////////////////////////////////////////////////////////////////////////////

template<typename R>
class function<R, void, void, void, void>
{
public:
	typedef R (*function_type)();
	typedef R (*callback_type)(void *);

	function() : _object( 0 ), _callback(), _static() {}
	function( function_type f ) : _object( 0 ), _callback(), _static( f ) {}
	template<class C>
	function( C * object ) : _object( object ), _callback( &method_callback<C, &C::operator()> ), _static() {}

	R operator () () const
	{
		return _static ? _static() : (*_callback)( _object );
	}

	template<class C, R (C::*Method)()>
	static function from_method( C * object )
	{
		return function( object, &method_callback<C, Method> );
	}

	template<class C, R (C::*Method)() const>
	static function from_method( C * object )
	{
		return function( object, &method_callback_const<C, Method> );
	}

	function & operator = ( const function & f )
	{
		_object   = f._object;
		_callback = f._callback;
		_static   = f._static;
		return *this;
	}

private:
	template<class C>
	function( C * object, callback_type callback ) : _object( object ), _callback( callback ), _static() {}

	template <class C, R (C::*Method)()>
	static R method_callback( void * object )
	{
		return ( static_cast<C *>( object ) ->*Method )();
	}

	template <class C, R (C::*Method)() const>
	static R method_callback_const( void * object )
	{
		return ( static_cast<C *>( object ) ->*Method )();
	}

	void          * _object;
	callback_type   _callback;
	function_type   _static;
};

////////////////////////////////////////////////////////////////////////////////

template<typename R, typename T1, typename T2, typename T3, typename T4>
inline std::ostream & operator << ( std::ostream & os, const function<R, T1, T2, T3, T4> & f )
{
	bool b( true );

	os << typeid(R).name() << '(';
	if ( b && typeid(T1) != typeid(void) ) os <<        typeid(T1).name(); else b = false;
	if ( b && typeid(T2) != typeid(void) ) os << ',' << typeid(T2).name(); else b = false;
	if ( b && typeid(T3) != typeid(void) ) os << ',' << typeid(T3).name(); else b = false;
	if ( b && typeid(T4) != typeid(void) ) os << ',' << typeid(T4).name(); else b = false;
	os << ')';
	return os;
}

}

#endif
