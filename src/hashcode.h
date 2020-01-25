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
	private:
		unsigned int maximumSlidesAmount;
		unsigned int pizzaAmount;
		unsigned int* slices;
	// friend std::ifstream& operator>>(std::ifstream&, Hashcode&);
};

#endif
