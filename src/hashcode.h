#ifndef __HASHCODE_H__
#define __HASHCODE_H__

#include <istream>
#include <fstream>
#include <iostream>
#include <vector>

class Hashcode {
	public:
		Hashcode();
		~Hashcode();
		void calculate();
		const unsigned int getNbSlice() const;
	private:
		// input
			unsigned long long int nbSliceMax;
			unsigned int nbPizza;
			unsigned int* slices;
		// output
			unsigned int nbSelectedPizza;
			bool* selected;
		// tempory
			unsigned long long int nbSlice;
	friend std::istream& operator>>(std::istream&, Hashcode&);
	friend std::ostream& operator<<(std::ostream&, Hashcode&);
};

#endif
