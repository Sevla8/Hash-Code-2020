#include "hashcode.h"

Hashcode::Hashcode() {}

Hashcode::~Hashcode() {}

void Hashcode::calculate() {
	this->nbSelectedPizza = 0;
	this->nbSlice = 0;

	unsigned int nbSliceTmp = 0;
	bool* selectedTmp = new bool[this->nbPizza];

	long long int it = this->nbPizza-1;
	while (this->slices[it] > this->nbSliceMax) --it;

	for (; it >=0; --it) {
		nbSliceTmp += this->slices[it];
		selectedTmp[it] = true;

		for (long long int jt = it-1; jt >= 0; --jt) {
			if (nbSliceTmp + this->slices[jt] < this->nbSliceMax) {
				nbSliceTmp += this->slices[jt];
				selectedTmp[jt] = true;
			}
		}


	}

	for (unsigned int i = 0; i <this->nbPizza; i += 1) {
		if (this->selected[i]) {
			this->nbSelectedPizza += 1;
		}
	}
}

std::istream& operator>>(std::istream& is, Hashcode& ha) {
	is >> ha.nbSliceMax;
	is >> ha.nbPizza;

	ha.slices = new unsigned int[ha.nbPizza];
	ha.selected = new bool[ha.nbPizza];
	for (unsigned int i = 0; i < ha.nbPizza; i += 1) ha.selected[i] = false;

	for (unsigned int it = 0; it < ha.nbPizza; ++it) {
		is >> ha.slices[it];
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, Hashcode& ha) {
	os << ha.nbSelectedPizza << std::endl;

	for (unsigned int it = 0; it < ha.nbPizza; ++it) {
		if (ha.selected[it]) {
			os << it << ' ';
		}
	}

	os << std::endl;

	delete[] ha.slices;
	delete[] ha.selected;

	return os;
}
