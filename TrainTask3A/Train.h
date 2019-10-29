#ifndef _TRAIN_H_
#define _TRAIN_H_

#include <iostream>
const unsigned MAX_LENGTH = 5;

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
		Car loco;
		stock[0] = loco;
	}
	//task 4 +
	std::istream& SetTrain(std::istream& s);
	//task 5 +
	std::ostream& ShowTrain(std::ostream& s);
	//task 6 +
	void TakePlaces(unsigned n, unsigned pass);
	//task 7 +
	unsigned GetTaken(unsigned n) const;
	unsigned GetMax(unsigned n) const;
	unsigned GetLength() const;

	//task 8 +
	Train AddCar(unsigned max0, unsigned taken0);
	Train AddCar(Car added); 
	//task 9 
	Train Divide(unsigned n, unsigned num[]);
	//task 10 +
	unsigned PassCount();
};

#endif