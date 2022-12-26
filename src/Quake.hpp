#ifndef QUAKE_HPP
#define QUAKE_HPP 1

#include <type_traits> // for is_floating_point
#include <limits>      // for numeric_limits
#include <climits>     // for CHAR_BIT
#include <cstdint>     // for int types uint32_t and uint64_t
#include <bit>         // bit_cast
#include "_power.hpp"  // pow2


constexpr static double correction_factor = 0.043035667;

namespace quake {

// Some constants related to a floating point
template <typename _T>
struct float_constants
{
private:
	// Only Work for Floating Points
	static_assert(
		std::is_floating_point<_T>::value);
	// Precision, aka number of bits of mantissa
	constexpr static unsigned short int p  = std::numeric_limits<_T>::digits;
	// number of exponent bits
	constexpr static unsigned short int ed = sizeof(_T) * CHAR_BIT - p;
public:
	// 2^(p-1)
	constexpr static double       L  = pow2(p - 1);
	// Bias in the exponent
	constexpr static unsigned int B  = (1u << (ed - 1)) - 1u;

};

// integer type to interpret the float value
template <typename _T>
struct int_type
{
	// Only Work for Floating Points
	static_assert(
		std::is_floating_point<_T>::value);
};

template<> struct  int_type<float>
{
	//Only support float => IEC 559 (IEEE 754) Single Precision
	static_assert(sizeof(float) * CHAR_BIT == 32);
	using type = uint32_t;
};

template<> struct  int_type<double>
{
	//Only support float => IEC 559 (IEEE 754) double Precision
	static_assert(sizeof(double) * CHAR_BIT == 64);
	using type = uint64_t;
};

// The magic number
template <typename _T>
constexpr static typename int_type<_T>::type magic_constant(void)
{
	using constants = float_constants<_T>;
	return static_cast<typename int_type<_T>::type> (
		1.5 * constants::L * (constants::B - correction_factor));
};

}

template<typename _T> _T Q_rsqrt(_T number) noexcept
{
	// Only Work for Floating Points
	static_assert(
		std::is_floating_point<_T>::value);
	// Only support IEC 559 (IEEE 754) float
	static_assert(
		std::numeric_limits<_T>::is_iec559);

	constexpr static _T threehalfs = static_cast<_T>(1.5);
	constexpr static _T half       = static_cast<_T>(0.5);

	using namespace quake;

	_T x = std::bit_cast<_T> (
		magic_constant<_T>()
			- (std::bit_cast<typename int_type<_T>::type>(number) >> 1)
	);
	// first iteration, can be commented out
	x *= threehalfs - (half * number* x * x);
	// second iteration
	return x * (threehalfs - (half * number * x * x));


};

#endif
