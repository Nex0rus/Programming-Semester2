#pragma once

template<const int count, const int val>
struct my_pow;


template<const int count, const int val>
struct my_pow
{
	static const int value = val * my_pow<count - 1, val>::value;
};


template<const int val>
struct my_pow<0, val> 
{	
	static const int value = 1;
};


template <const int count, const int val, const int... args>
struct polynom;


template<const int count, const int val>
struct polynom<count, val>
{
	static const int value = 0;
};


template <const int count, const int val, const int first, const int ... coeff>
struct polynom<count, val, first, coeff...>
{
	static const int value = my_pow<count, val>::value * first + polynom<count + 1, val, coeff...>::value;
};


template <const int val, const int ... coeff>
struct polynom_value
{
	static const int value_v = polynom<0, val, coeff...>::value;
};


template<const int ... coeff>
std::ostream& operator<<(std::ostream& os, polynom<coeff...>& p)
{ int count = 0; ( (os << coeff << "x^" << ++count << " "), ...); return os;}
