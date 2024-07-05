#include "parser.hpp"
#include "utils.hpp"

#include <iostream>
#include <string>
#include <regex>

int main(int argc, char** argv) {
	VERIFY_CONTRACT(argc == 2, "Unexpected arguments");

	std::string filename{ argv[1] };

	VERIFY_CONTRACT(std::regex_match(filename, std::regex("[A-Za-z_\\/\\-]+\\.lng")), "Invalid file format");

    std::cout << BYELLOW << "Building program " << BCYAN << filename << RESET << std::endl;

	Parser parser = Parser(filename);
	std::string ofilename = filename.replace(filename.size() - 3, 3, "bcode");
	parser.parse(ofilename);

	return 0;
}