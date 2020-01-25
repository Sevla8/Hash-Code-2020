#ifndef __HASHCODE_H__
#define __HASHCODE_H__

#include <istream>
#include <fstream>
// #include <assert.h>
// #include <math.h>

class Hashcode {
	public:
		Hashcode();
		~Hashcode();
		void calculate();
	private:
		// input
			unsigned int maximumSliceAmount;
			unsigned int pizzaAmount;
			unsigned int* slices;
		// output
			unsigned int resultPizzaAmount;
			unsigned int* resultSlices;
	friend std::istream& operator>>(std::istream&, Hashcode&);
	friend std::ostream& operator<<(std::ostream&, Hashcode&);
};

#endif
