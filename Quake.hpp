#ifndef QUAKE_HPP
#define QUAKE_HPP

#include <type_traits>
#include <limits>
#include <climits>

template<typename _T> _T Q_rsqrt(_T number)
{ static_assert(std::is_floating_point<_T>::value,""); };


template<>
float Q_rsqrt(float number)
{
	static_assert(std::numeric_limits<float>::is_iec559, "Only support IEC 559 (IEEE 754) float");
	static_assert(sizeof(float) * CHAR_BIT == 32, "Only support float => Single Precision IEC 559 (IEEE 754)");
}

template<>
double Q_rsqrt(double number)
{
	static_assert(std::numeric_limits<float>::is_iec559, "Only support IEC 559 (IEEE 754) double");
	static_assert(sizeof(float) * CHAR_BIT == 32, "Only support double => Double Precision IEC 559 (IEEE 754)");
}

template<>
long double Q_rsqrt(long double number)
{
	static_assert(std::numeric_limits<float>::is_iec559, "Only support IEC 559 (IEEE 754) long double");
	static_assert(sizeof(float) * CHAR_BIT == 32, "Only support long double => Exteneded Precision IEC 559 (IEEE 754)");

}

#endif
