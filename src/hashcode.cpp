#include "hashcode.h"

Hashcode::Hashcode() {}

Hashcode::~Hashcode() {
	delete[] this->slices;
}

// std::ifstream& operator>>(std::ifstream& is, Hashcode& ha) {

// 	return is;
// }
