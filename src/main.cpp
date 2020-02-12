#include <iostream>
#include <fstream>
#include <string>
#include "hashcode.h"

int main(int argc, const char** argv) {
	if (argc != 2) {
		std::cout << "Syntaxe d'appel: ./hashcode <input_file>" << std::endl;
		return 1;
	}

	std::string inputFileName = argv[1];
	std::ifstream inputFile(inputFileName.c_str());
	if (inputFile.fail()) {
		std::cerr << "Input ERROR '" << inputFileName << "' !" << std::endl;
		return 2;
	}
	std::string outputFileName = "";
	std::string::const_iterator it = inputFileName.begin();
	while (*it != 'i') {
		outputFileName += *it;
		++it;
	}
	outputFileName += "out";
	++it;
	++it;
	while (*it != '.') {
		outputFileName += *it;
		++it;
	}
	outputFileName += ".out";
	std::ofstream outputFile(outputFileName.c_str());
	if (outputFile.fail()) {
		std::cerr << "Output ERROR '" << outputFileName << "' !" << std::endl;
		return 3;
	}

	Hashcode hashcode;

	inputFile >> hashcode;

	hashcode.calculate();

	std::cout << hashcode.getNbSlices() << std::endl;

	outputFile << hashcode;

	return 0;
}
