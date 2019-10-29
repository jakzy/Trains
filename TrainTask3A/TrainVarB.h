#ifndef _TRAIN_H_
#define _TRAIN_H_

#include <iostream>
const unsigned MAX_LENGTH = 6;

unsigned GetNum(const char* msg);
unsigned GetNum(const char* msg, std::istream& i);
void Swap(unsigned &a, unsigned &b);
struct Car {
	unsigned max;
	unsigned taken;
	//task 1,2 +
	Car(unsigned MAX = 0, unsigned TAKEN = 0) : max(MAX), taken(TAKEN) {
		if (TAKEN > MAX)
			throw std::exception("This car can't exist");
	}
};

class Train {
private:
	unsigned length;
	Car stock[MAX_LENGTH];
public:
	//task 3 +
	Train() : length(1) {
		stock[0] = Car();
	}
	Train(Car add) {
		stock[0] = Car();
		if (add.max) {
			stock[1] = add;
			length = 2;
		}
		else length = 1;
	}
	//task 4 +
	friend std::istream& operator >> (std::istream& s, Train &a);
	//task 5 +
	friend std::ostream& operator << (std::ostream& s, const Train &a);
	//task 6 +
	void operator ()(unsigned n, unsigned pass);
	//task 7 +
	const unsigned& operator [] (unsigned n) const;
	unsigned& operator [] (unsigned n);
	unsigned GetMax(unsigned n) const;
	unsigned GetLength() const;

	//task 8 +
	Train& operator +=(Train added);

	//task 9 
	Train operator ()(unsigned n, unsigned num[]);
	//task 10 +
	unsigned PassCount();
	//task 11
	friend Train operator+ (Train t1, Train t2);
};

#endif