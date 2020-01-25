#include "hashcode.h"

Hashcode::Hashcode() {
	this->slices = new unsigned int[0];
	this->resultSlices = new unsigned int[0];
}

Hashcode::~Hashcode() {
	delete[] this->slices;
	delete[] this->resultSlices;
}

void Hashcode::calculate() {

}

std::istream& operator>>(std::istream& is, Hashcode& ha) {
	is >> ha.maximumSliceAmount;
	is >> ha.pizzaAmount;

	delete[] ha.slices;
	delete[] ha.resultSlices;
	ha.slices = new unsigned int[ha.pizzaAmount];
	ha.resultSlices = new unsigned int[ha.pizzaAmount];

	for (unsigned int it = 0; it < ha.pizzaAmount; ++it) {
		is >> ha.slices[it];
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, Hashcode& ha) {
	os << ha.resultPizzaAmount << std::endl;

	for (unsigned int it = 0; it < ha.resultPizzaAmount; ++it) {
		os << ha.resultSlices[it] << ' ';
	}

	os << std::endl;

	return os;
}
