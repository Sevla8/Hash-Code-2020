#include <iostream>
#include <fstream>
#include "hashcode.h"

int main(int argc, const char** argv) {
	if (argc != 2) {
		std::cout << "Syntaxe d'appel: ./hashcode <input_file>" << std::endl;
		return 1;
	}

	std::ifstream inputFile(argv[1]);
	if (inputFile.fail()) {
		std::cerr << "Input ERROR '" << argv[1] << "'" << std::endl;
			return 1;
	}

	// Hashcode hashcode();
	// inputFile >> hashcode;

	return 0;
}
