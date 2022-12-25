#ifndef QUAKE_HPP
#define QUAKE_HPP 1

#include <type_traits>
#include <limits>
#include <climits>
#include <cmath>
#include <cstdint>
#include <bit>
#include "power.hpp"

template<typename _T> _T Q_rsqrt(_T number) noexcept
{ static_assert(std::is_floating_point<_T>::value,"Only Work for Floating Points"); };

constexpr static double _correction_factor = 0.043;

template <typename _T>
struct float_prperties
{
private:
	constexpr static unsigned short int p  = std::numeric_limits<_T>::digits - 1;
	constexpr static unsigned short int ed = sizeof(_T) * CHAR_BIT - p - 1;
public:
	constexpr static double L    = pow2(p);
	constexpr static int    Bias = static_cast<int>(pow2(ed - 1)) - 1;
};

template <typename _T>
struct int_type
{ static_assert(std::is_floating_point<_T>::value,"Only Work for Floating Points"); };

template<> struct  int_type<float>
{
	using type = uint32_t;
};

template<> struct  int_type<double>
{
	using type = uint64_t;
};

template <typename _T>
constexpr static typename int_type<_T>::type constant(void)
{
	using properties = float_prperties<_T>;
	return static_cast<typename int_type<_T>::type> (1.5 * properties::L * (properties::Bias - _correction_factor));
};


template<>
float Q_rsqrt(float number) noexcept
{
	static_assert(std::numeric_limits<float>::is_iec559, "Only support IEC 559 (IEEE 754) float");
	static_assert(sizeof(float) * CHAR_BIT == 32, "Only support float => Single Precision IEC 559 (IEEE 754)");

	const float x = std::bit_cast<float>(constant<float>() - (std::bit_cast<typename int_type<float>::type>(number) >> 1));

	return x * (1.5f - (number * 0.5f * x * x));
}

template<>
double Q_rsqrt(double number) noexcept
{
	static_assert(std::numeric_limits<double>::is_iec559, "Only support IEC 559 (IEEE 754) double");
	static_assert(sizeof(double) * CHAR_BIT == 64, "Only support double => Double Precision IEC 559 (IEEE 754)");

	return number;
}

template<>
long double Q_rsqrt(long double number) noexcept
{
	static_assert(std::numeric_limits<long double>::is_iec559, "Only support IEC 559 (IEEE 754) long double");
	static_assert(sizeof(float) * CHAR_BIT == 32, "Only support long double => Exteneded Precision IEC 559 (IEEE 754)");

	return number;
}

#endif
