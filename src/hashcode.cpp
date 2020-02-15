#include "hashcode.h"

Hashcode::Hashcode() {}

Hashcode::~Hashcode() {}

void Hashcode::calculate() {
	this->nbSelectedPizza = 0;
	this->nbSlice = 0;

	long int index = this->nbPizza;
	unsigned long long int tmpNbSlice = 0;
	std::vector<unsigned int> tmpSlicesIndex;

	while (index >= 0) {
		index -= 1;

		for (long long int it = index; it >= 0; --it) {
			if (tmpNbSlice + this->slices[it] <= this->nbSliceMax && !this->selected[it]) {
				tmpNbSlice += this->slices[it];
				tmpSlicesIndex.push_back(it);
			}
			if (tmpNbSlice == this->nbSliceMax) {
				break;
			}
		}
		if (this->nbSlice < tmpNbSlice) {
			this->nbSlice = tmpNbSlice;
			for (unsigned int i = 0; i < this->nbPizza; i += 1) {
				this->selected[i] = false;
			}
			for (std::vector<unsigned>::iterator jt = tmpSlicesIndex.begin(); jt != tmpSlicesIndex.end(); ++jt) {
				this->selected[*jt] = true;
			}
		}
		if (this->nbSlice == this->nbSliceMax) {
			break;
		}
		if (tmpSlicesIndex.size() != 0) {
			index = tmpSlicesIndex[tmpSlicesIndex.size()-1];
			tmpSlicesIndex.pop_back();
			tmpNbSlice -= this->slices[index];
		}
	}
}

const unsigned int Hashcode::getNbSlice() const {
	return this->nbSlice;
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
