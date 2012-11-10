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

#ifndef OT_RANDOM_HPP
#define OT_RANDOM_HPP

#include <cstdlib>
#include <stdint.h>

namespace ot
{

/*
	Class: linear_congruential_engine<...>

	(C++11) A linear congruential random number generator implementation.
*/
template<typename UINT, UINT A, UINT C, UINT M>
class linear_congruential_engine
{
public:
	typedef UINT result_type;

	static const result_type multiplier   = A;
	static const result_type increment    = C;
	static const result_type modulus      = M;
	static const result_type default_seed = 1u;

	explicit linear_congruential_engine( result_type value = default_seed );
	void seed( result_type value = default_seed );

	result_type operator () ();
	void discard( unsigned long z );

	static result_type min();
	static result_type max();

private:
	result_type _data;
};

/*
	Class: mersenne_twister_engine<...>

	(C++11) A Mersenne Twister random number generator implementation.

	See:
		http://www.math.sci.hiroshima-u.ac.jp/~m-mat/MT/emt.html
*/
template<
	typename UINT,   // Result type.
	std::size_t W,   // Word size.
	std::size_t N,   // State size.
	std::size_t M,   // Shift size.
	std::size_t R,   // Mask bits.
	UINT A,          // XOR mask.
	std::size_t U,   // Tempering u.
	UINT D,          // Tempering d.
	std::size_t S,   // Tempering s.
	UINT B,          // Tempering b.
	std::size_t T,   // Tempering t.
	UINT C,          // Tempering c.
	std::size_t L,   // Tempering l.
	UINT F>          // Initialization multiplier.
class mersenne_twister_engine
{
public:
	typedef UINT result_type;

	static const std::size_t word_size                 = W;
	static const std::size_t state_size                = N;
	static const std::size_t shift_size                = M;
	static const std::size_t mask_bits                 = R;
	static const result_type xor_mask                  = A;
	static const std::size_t tempering_u               = U;
	static const std::size_t tempering_d               = D;
	static const std::size_t tempering_s               = S;
	static const result_type tempering_b               = B;
	static const std::size_t tempering_t               = T;
	static const result_type tempering_c               = C;
	static const std::size_t tempering_l               = L;
	static const result_type initialization_multiplier = C;
	static const result_type default_seed              = 5489u;

	explicit mersenne_twister_engine( result_type value = default_seed );
	void seed( result_type value = default_seed );

	result_type operator () ();
	void discard( unsigned long z );

	static result_type min();
	static result_type max();

private:
	static const result_type MASK  = ~((~0ul-1ul) << (W-1));
	static const result_type UMASK = ( ~UINT() ) << R;
	static const result_type LMASK = ~UMASK;

	std::size_t index;
	result_type MT[N];
};

////////////////////////////////////////////////////////////////////////////////

/*
	Class: minstd_rand0

	(C++11) Minimal Standard minstd_rand0 generator.
*/
typedef linear_congruential_engine<uint_fast32_t, 16807, 0, 2147483647> minstd_rand0;

/*
	Class: minstd_rand

	(C++11) Minimal Standard minstd_rand generator.
*/
typedef linear_congruential_engine<uint_fast32_t, 48271, 0, 2147483647> minstd_rand;

/*
	Class: mt19937

	(C++11) A well known variant of Mersenne Twister.
*/
typedef mersenne_twister_engine<uint_fast32_t, 32, 624, 397, 31, 
	0x9908b0df, 11, 
	0xffffffff, 7, 
	0x9d2c5680, 15, 
	0xefc60000, 18, 1812433253ul>
	mt19937;

/*
	Class: default_random_engine

	(C++11) This is a random number engine class that generates pseudo-random numbers.
*/
typedef minstd_rand0 default_random_engine;

////////////////////////////////////////////////////////////////////////////////

template<typename UINT, UINT A, UINT C, UINT M>
linear_congruential_engine<UINT,A,C,M>::linear_congruential_engine( result_type value )
{
	seed( value );
}

template<typename UINT, UINT A, UINT C, UINT M>
void linear_congruential_engine<UINT,A,C,M>::seed( result_type value )
{
	_data = ( increment % modulus == 0 && value % modulus == 0 ) ? default_seed : ( value % modulus );
}

template<typename UINT, UINT A, UINT C, UINT M>
typename linear_congruential_engine<UINT,A,C,M>::result_type linear_congruential_engine<UINT,A,C,M>::operator () ()
{
	if ( multiplier == 1 )
	{
		_data %= modulus;
	}
	else
	{
		static const result_type q = modulus / multiplier;
		static const result_type r = modulus % multiplier;
		result_type t1 = multiplier * ( _data % q );
		result_type t2 = r * ( _data / q );

		_data = ( t1 < t2 ) ? ( modulus + t1 - t2 ) : ( t1 - t2 );
	}

	if ( increment != 0 )
	{
		const result_type d = modulus - _data;

		if ( d > increment )
			_data += increment;
		else
			_data = increment - d;
	}
	return _data;
}

template<typename UINT, UINT A, UINT C, UINT M>
void linear_congruential_engine<UINT,A,C,M>::discard( unsigned long z )
{
	for ( ; z != 0; --z )
	{
		(*this)();
	}
}

template<typename UINT, UINT A, UINT C, UINT M>
typename linear_congruential_engine<UINT,A,C,M>::result_type linear_congruential_engine<UINT,A,C,M>::min()
{
	return increment == 0u ? 1u : 0u;
}

template<typename UINT, UINT A, UINT C, UINT M>
typename linear_congruential_engine<UINT,A,C,M>::result_type linear_congruential_engine<UINT,A,C,M>::max()
{
	return modulus - 1u;
}

////////////////////////////////////////////////////////////////////////////////

template<typename UINT, std::size_t W, std::size_t N, std::size_t M,
	std::size_t R, UINT A, std::size_t U, UINT D, std::size_t S, UINT B,
	std::size_t T, UINT C, std::size_t L, UINT F>
mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::mersenne_twister_engine( result_type value )
{
	seed( value );
}

template<typename UINT, std::size_t W, std::size_t N, std::size_t M,
	std::size_t R, UINT A, std::size_t U, UINT D, std::size_t S, UINT B,
	std::size_t T, UINT C, std::size_t L, UINT F>
void mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::seed( result_type value )
{
	MT[0] = value & MASK;
	for ( std::size_t i = 1; i < N; ++i )
	{
		MT[i] = ( F * ( MT[i-1] ^ ( MT[i-1] >> ( W - 2 ) ) ) + i ) & MASK;
	}
	index = state_size;
}

template<typename UINT, std::size_t W, std::size_t N, std::size_t M,
	std::size_t R, UINT A, std::size_t U, UINT D, std::size_t S, UINT B,
	std::size_t T, UINT C, std::size_t L, UINT F>
typename mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::result_type mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::operator () ()
{
	std::size_t i;
	result_type y;

	if ( index >= state_size )
	{
		for ( i = 0; i < (N - M); ++i)
		{
			y = ( MT[i] & UMASK ) | ( MT[i + 1] & LMASK );
			MT[i] = MT[i + M] ^ ( y >> 1 ) ^ ( ( y & 0x01 ) ? A : 0 );
		}

		for ( i = (N - M); i < (N - 1); ++i )
		{
			y = ( MT[i] & UMASK ) | ( MT[i + 1] & LMASK );
			MT[i] = MT[i + (M - N)] ^ ( y >> 1 ) ^ ( ( y & 0x01 ) ? A : 0);
		}

		y = ( MT[N - 1] & UMASK ) | ( MT[0] & LMASK );
		MT[N - 1] = MT[M - 1] ^ ( y >> 1 ) ^ ( ( y & 0x01 ) ? A : 0 );
		index = 0;
	}

	y = MT[index++];
	y ^= ( y >> U ) & D;
	y ^= ( y << S ) & B;
	y ^= ( y << T ) & C;
	y ^= ( y >> L );
	return y;
}

template<typename UINT, std::size_t W, std::size_t N, std::size_t M,
	std::size_t R, UINT A, std::size_t U, UINT D, std::size_t S, UINT B,
	std::size_t T, UINT C, std::size_t L, UINT F>
void mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::discard( unsigned long z )
{
	for ( ; z != 0; --z )
	{
		(*this)();
	}
}

template<typename UINT, std::size_t W, std::size_t N, std::size_t M,
	std::size_t R, UINT A, std::size_t U, UINT D, std::size_t S, UINT B,
	std::size_t T, UINT C, std::size_t L, UINT F>
typename mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::result_type mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::min()
{
	return 0;
}

template<typename UINT, std::size_t W, std::size_t N, std::size_t M,
	std::size_t R, UINT A, std::size_t U, UINT D, std::size_t S, UINT B,
	std::size_t T, UINT C, std::size_t L, UINT F>
typename mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::result_type mersenne_twister_engine<UINT,W,N,M,R,A,U,D,S,B,T,C,L,F>::max()
{
	return MASK;
}

}

#endif
