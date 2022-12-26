#include <iostream>
#include "Quake.hpp"
#include <getopt.h>
#include <string>
#include <cmath>
#include <stdexcept>
#include <iomanip>

extern char *optarg;
extern int optind;
extern int opterr;   // disable automatic error message
extern int optopt;

static int long_opt_index = 0;
static const option long_opts[]
	= {
		{ "double", 0, NULL, 'd' },
		{ "float", 0, NULL, 'f' },
		{ "help", 0, NULL, 'h' },
		{ 0, 0, 0, 0 }
	};

static const char helpmsg[]
	=   "  -d, --double\t\tUse IEC 559 (IEEE 754) double precision (the defualt)\n"
		"  -f, --float\t\tUse IEC 559 (IEEE 754) single precision\n"
		"  -h, --help\t\tPrint this message\n";

int main(int argc, char **argv)
{
	int opt;
	int ftl_tp = 'd';

	while ((opt = getopt_long(argc, argv, "fdh", long_opts, &long_opt_index)) != -1)
		switch(opt) {
			case 'f':
				ftl_tp = 'f';
				break;
			case 'd':
				ftl_tp = 'd';
				break;
			case 'h':
				std::cout << "usage: " << *argv
				<< " [options] -- <number>\n\n" << helpmsg;
				return 0;
			case '?':
				return 1;
		}

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
