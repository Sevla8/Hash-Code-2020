#include "hashcode.h"

Hashcode::Hashcode() {}

Hashcode::~Hashcode() {}

void Hashcode::calculate() {
	this->nbSelectedPizza = 0;
	this->nbSlice = 0;

	for (unsigned int it = 0; it < this->nbPizza; ++it) {
		unsigned int nbSliceTmp = this->slices[it];
		bool* selectedTmp = new bool[this->nbPizza];
		for (unsigned int i = 0; i < this->nbPizza; i += 1) {
			selectedTmp[i] = false;
		}
		selectedTmp[it] = true;

		this->calculate(nbSliceTmp, selectedTmp);

		if (nbSliceTmp > this->nbSlice && nbSliceTmp <= this->nbSliceMax) {
			this->nbSlice = nbSliceTmp;
			for (unsigned int i = 0; i < this->nbPizza; i += 1) {
				this->selected[i] = selectedTmp[i];
			}
		}

		delete[] selectedTmp;

	}

	for (unsigned int i = 0; i < this->nbPizza; i += 1) {
		if (this->selected[i]) this->nbSelectedPizza += 1;
	}
}

void Hashcode::calculate(unsigned int& nbSliceTmp, bool*& selectedTmp) {
	if (nbSliceTmp < this->nbSliceMax) {
		for (unsigned int it = 0; it < this->nbPizza; ++it) {
			if (selectedTmp[it] == false) {

				unsigned int nbSliceTmp2 = nbSliceTmp + this->slices[it];
				bool* selectedTmp2 = new bool[this->nbPizza];
				for (unsigned int i = 0; i < this->nbPizza; i += 1) {
					selectedTmp2[i] = selectedTmp[i];
				}
				selectedTmp2[it] = true;

				if (nbSliceTmp2 > this->nbSlice && nbSliceTmp2 <= this->nbSliceMax) {
					this->nbSlice = nbSliceTmp2;
					for (unsigned int i = 0; i < this->nbPizza; i += 1) {
						this->selected[i] = selectedTmp2[i];
					}
				}

				this->calculate(nbSliceTmp2, selectedTmp2);

				delete[] selectedTmp2;

			}
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
