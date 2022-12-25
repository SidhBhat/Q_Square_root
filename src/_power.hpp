#ifndef POWER_HPP
#define POWER_HPP 1

#include <cstdint>

constexpr double pow2(uint16_t n)
{
	double x = 1.0;

	while(n-- >= 1)
		x *= 2.0;
	return x;
}

#endif // POWER_HPP_INCLUDED
