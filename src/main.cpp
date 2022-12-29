#include <iostream>    // input output
#include "Quake.hpp"   // Quake Alogorithm
// credit: @jarro2783 on Github (https://github.com/jarro2783)
#include "../cxxopts/include/cxxopts.hpp"  // external library to pharse commandline
#include <string>      // for  std::stod
#include <cmath>       // for std::sqrt
#include <stdexcept>   // for std::invalid_argument & std::out_of_range
#include <iomanip>     // for std::setprecision

#include <assert.h>

#define PROGRAM_NAME "quaketest"

// const paranoia
int main(const int argc, const char *const *const argv)
{
	// flag to determine float type
	int ftl_tp = 'd';

	// Set up options
	cxxopts::Options options(PROGRAM_NAME,"Program to test Q_rsqrt()");
	options.add_options()
		("d,double", "Use IEC 559 (IEEE 754) double precision (the defualt)")
		("f,float",  "Use IEC 559 (IEEE 754) single precision")
		("h,help",   "Print this message")
		("number",   "The number to give Q_rsqrt", cxxopts::value<std::string>());
	// positional options
	options.parse_positional("number");
	options.positional_help("<NUMBER>");

	std::string num; // string to hold the number
	try {
		// pharse the options
		auto result = options.parse(argc, argv);
		// print help
		if(result.count("help")) {
			std::cout << options.help() << std::endl;
			return 0;
		}

		const auto argvec = result.arguments();
		auto       it     = argvec.begin();
		const auto it_end = argvec.end();
		/* Pharse -f and -d in the order they come
		 * set flag to the last flag on the commandline
		 */
		while(it != it_end)
		{
			if (!(*it).key().compare("double"))
				ftl_tp = 'd';
			else if(!(*it).key().compare("float"))
				ftl_tp = 'f';
			it++;
		}
		// fetch the number
		num = argvec.back().value();
	}
	catch (const cxxopts::exceptions::parsing &ex) {
		std::cout << "Error while pharsing commandline: "
			<< ex.what() << std::endl;
	}

	try {
		std::cout << std::setprecision(10);  // set 10 digits of precision
		switch(ftl_tp) {
			case 'd': {
					double x = std::stod(num); // convert string to number
					std::cout << "x => Double precision IEEE 754" << std::endl;
					std::cout << "x =\t\t" << x << std::endl;
					std::cout << "1/sqrt(x)  =\t" << 1/std::sqrt(x) << std::endl;
					std::cout << "Q_rsqrt(x) =\t" << Q_rsqrt(x) << std::endl;
				}
				break;
			case 'f': {
					float x = std::stod(num); // convert string to number
					std::cout << "x => Single precision IEEE 754" << std::endl;
					std::cout << "x =\t\t" << x << std::endl;
					std::cout << "1/sqrt(x) =\t" << 1/std::sqrt(x) << std::endl;
					std::cout << "Q_rsqrt(x) =\t" << Q_rsqrt(x) << std::endl;
				}
				break;
		}
	}
	catch(const std::invalid_argument & exp1 ) {
		std::cout << "Not a valid number: "
			<< num << std::endl;
		return 2;
	}
	catch(const std::out_of_range & exp2 ) {
		std::cout << "Number is out of range: "
		<< num << std::endl;
		return 2;
	}

	return 0;
}
