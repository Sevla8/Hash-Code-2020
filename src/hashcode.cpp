#include "hashcode.h"

Hashcode::Hashcode() {}

Hashcode::~Hashcode() {}

void Hashcode::calculate() {
	this->nbSelectedPizza = 0;
	this->nbSlice = 0;

	for (long it = this->nbPizza-1; it >= 0; --it) {
		unsigned long long int nbSliceTmp = 0;
		bool* selectedTmp = new bool[this->nbPizza];
		for (long i = 0; i < this->nbPizza; i += 1) {
			selectedTmp[i] = false;
		}

		for (unsigned int jt = it; jt >= 0; --jt) {
			if (nbSliceTmp + this->slices[jt] <= this->nbSliceMax) {
				nbSliceTmp += this->slices[jt];
				selectedTmp[jt] = true;
			}
		}

		if (nbSliceTmp > this->nbSlice) {
			this->nbSlice = nbSliceTmp;
			for (unsigned int i = 0; i < this->nbPizza; i += 1) {
				this->selected[i] = selectedTmp[i];
			}
		}

		delete[] selectedTmp;

		if (this->nbSlice == this->nbSliceMax) break;
	}

	for (unsigned int i = 0; i < this->nbPizza; i += 1) {
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
