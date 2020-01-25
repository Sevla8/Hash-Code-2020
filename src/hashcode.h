#ifndef __HASHCODE_H__
#define __HASHCODE_H__

#include <istream>
#include <fstream>
#include <iostream>

class Hashcode {
	public:
		Hashcode();
		~Hashcode();
		void calculate();
		void calculate(unsigned int&, bool*&);
	private:
		// input
			unsigned int maximumSliceAmount;
			unsigned int pizzaAmount;
			unsigned int* slices;
		// output
			unsigned int resultPizzaAmount;
			bool* selectedPizza;
		// tempory
			unsigned int sliceAmount;
	friend std::istream& operator>>(std::istream&, Hashcode&);
	friend std::ostream& operator<<(std::ostream&, Hashcode&);
};

#endif
