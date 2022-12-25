#include <iostream>
#include "Quake.hpp"

int main(void)
{
	float x = std::numeric_limits<float>::max();

	std::cout << x << std::endl;
	std::cout << Q_rsqrt(x) << std::endl;
}
