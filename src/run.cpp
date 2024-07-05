#include <iostream>
#include <string>

#include "parser.hpp"
#include "cpu.hpp"

#define BRED    "\033[1;31m"
#define BGREEN  "\033[1;32m"
#define BYELLOW "\033[1;33m"
#define GREEN   "\033[1;35m"
#define BCYAN   "\033[1;36m"
#define RESET   "\033[0m"

int main(int argc, char** argv) {
	VERIFY_CONTRACT(argc == 2, "Unexpected arguments");

	std::string filename { argv[1] };

	VERIFY_CONTRACT(std::regex_match(filename, std::regex("[A-Za-z_\\/\\-]+\\.bcode")), "Invalid file format");

	CPU cpu { CPU(filename) };

	std::cout << BYELLOW << "Running program " << BCYAN << filename << RESET << std::endl;

	cpu.run();

	return 0;
}