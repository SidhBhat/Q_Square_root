#include <iostream>    // input output
#include "Quake.hpp"   // Quake Alogorithm
// credit: @jarro2783 on Github (https://github.com/jarro2783)
#include "../cxxopts/include/cxxopts.hpp"  // external library to pharse commandline
#include <string>      // for  std::stod
#include <cmath>       // for std::sqrt
#include <stdexcept>   // for std::invalid_argument & std::out_of_range
#include <iomanip>     // for std::setprecision

#define PROGRAM_NAME "quaketest"

static const std::string helpmsg
	=   "  -d, --double\t\tUse IEC 559 (IEEE 754) double precision (the defualt)\n"
		"  -f, --float\t\tUse IEC 559 (IEEE 754) single precision\n"
		"  -h, --help\t\tPrint this message\n";

int main(int argc, char **argv)
{
	int ftl_tp = 'k';

	cxxopts::Options options(PROGRAM_NAME,"Program to test Q_rsqrt()");
	try {
		options.add_options()
		("d,double", "Use Double precision IEEE 754")
		("f,float", "Use Single precision IEEE 754")
		("h,help","Print Help");

		auto result = options.parse(argc, argv);

		if(result.count("help")) {
			std::cout << "Usage: " << *argv
				<< " [options] -- <number>\n" << std::endl;
			std::cout << helpmsg << std::endl;
			return 0;
		}

		auto it           = result.begin();
		const auto it_end = result.end();

		while(it != it_end)
		{
			static const bool exits_d = result["double"].count();
			static const bool exits_f = result["float"].count();

			if(exits_d) {
				if (!(*it).key().compare("double"))
					ftl_tp = 'd';
			}
			if(exits_f) {
				if(!(*it).key().compare("float"))
					ftl_tp = 'f';
			}
			std::cout << "loop" << '\n';
			it++;
		}
		std::cout << "ftl_tp:" << (char)ftl_tp << std::endl;

	}
	catch (const cxxopts::exceptions::parsing &ex)
	{
		std::cout << "Error while pharsing commandline: "
			<< ex.what() << std::endl;
	}

	return 9;
	try {
		switch(ftl_tp) {
			case 'd': {
					double x = std::stod(*(argv + optind));
					std::cout << std::setprecision(10);
					std::cout << "x => Double precision IEEE 754" << std::endl;
					std::cout << "x =\t\t" << x << std::endl;
					std::cout << "1/sqrt(x)  =\t" << 1/std::sqrt(x) << std::endl;
					std::cout << "Q_rsqrt(x) =\t" << Q_rsqrt(x) << std::endl;
				}
				break;
			case 'f': {
					float x = std::stod(*(argv + optind));
					std::cout << std::setprecision(10);
					std::cout << "x => Single precision IEEE 754" << std::endl;
					std::cout << "x =\t\t" << x << std::endl;
					std::cout << "1/sqrt(x) =\t" << 1/std::sqrt(x) << std::endl;
					std::cout << "Q_rsqrt(x) =\t" << Q_rsqrt(x) << std::endl;
				}
				break;
		}
	}
	catch(const std::invalid_argument & exp1 ) {
		std::cout << "Not a inavlid number: "
			<< *(argv + optind) << std::endl;
		return 2;
	}
	catch(const std::out_of_range & exp2 ) {
		std::cout << "Number is out of range: "
		<< *(argv + optind) << std::endl;
		return 2;
	}

	return 0;
}
