#include "hashcode.h"

Hashcode::Hashcode() {}

Hashcode::~Hashcode() {}

void Hashcode::calculate() {
	this->resultPizzaAmount = 0;
	this->sliceAmount = 0;
	for (unsigned int it = 0; it < this->pizzaAmount; ++it) {
		unsigned int sliceAmount = this->slices[it];
		bool* selectedPizza = new bool[pizzaAmount];
		for (unsigned int i = 0; i < pizzaAmount; i += 1) {
			selectedPizza[i] = false;
		}
		selectedPizza[it] = true;

		this->calculate(sliceAmount, selectedPizza);

		if (sliceAmount > this->sliceAmount && sliceAmount <= this->maximumSliceAmount) {
			this->sliceAmount = sliceAmount;
			for (unsigned int i = 0; i < this->pizzaAmount; i += 1) {
				this->selectedPizza[i] = selectedPizza[i];
			}
		}

		delete[] selectedPizza;

	}

	for (unsigned int i = 0; i < this->pizzaAmount; i += 1) {
		if (this->selectedPizza[i]) this->resultPizzaAmount += 1;
	}
}

void Hashcode::calculate(unsigned int& sliceAmount, bool*& selectedPizza) {
	if (sliceAmount < this->maximumSliceAmount) {
		for (unsigned int it = 0; it < this->pizzaAmount; ++it) {
			if (selectedPizza[it] == false) {

				unsigned int sliceAmount0 = sliceAmount + this->slices[it];
				bool* selectedPizza0 = new bool[pizzaAmount];
				for (unsigned int i = 0; i < this->pizzaAmount; i += 1) {
					selectedPizza0[i] = selectedPizza[i];
				}
				selectedPizza0[it] = true;

				if (sliceAmount0 > this->sliceAmount && sliceAmount0 <= this->maximumSliceAmount) {
					this->sliceAmount = sliceAmount0;
					for (unsigned int i = 0; i < this->pizzaAmount; i += 1) {
						this->selectedPizza[i] = selectedPizza0[i];
					}
				}

				this->calculate(sliceAmount0, selectedPizza0);

				delete[] selectedPizza0;

			}
		}
	}
}

std::istream& operator>>(std::istream& is, Hashcode& ha) {
	is >> ha.maximumSliceAmount;
	is >> ha.pizzaAmount;

	ha.slices = new unsigned int[ha.pizzaAmount];
	ha.selectedPizza = new bool[ha.pizzaAmount];

	for (unsigned int it = 0; it < ha.pizzaAmount; ++it) {
		is >> ha.slices[it];
	}

	return is;
}

std::ostream& operator<<(std::ostream& os, Hashcode& ha) {
	os << ha.resultPizzaAmount << std::endl;

	for (unsigned int it = 0; it < ha.pizzaAmount; ++it) {
		if (ha.selectedPizza[it]) {
			os << it << ' ';
		}
	}

	os << std::endl;

	delete[] ha.slices;
	delete[] ha.selectedPizza;

	return os;
}
