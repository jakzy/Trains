#ifndef _TRAIN_H_
#define _TRAIN_H_

#include <iostream>

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


Car* Realloc(Car* oldSt, unsigned oldSZ, unsigned newSZ);

class Train {
private:
	unsigned length;
	Car* stock;
public:
	//task 3 +
	Train() : length(1) {
		stock = new Car[1];
		stock[0] = Car();
		std::cout << "*****Default constructor used*****" << std::endl;
	}
	Train(Car add) {
		if (add.max) {
			stock = new Car[2];
			stock[0] = Car();
			stock[1] = add;
			length = 2;
		}
		else {
			stock = new Car[1];
			stock[0] = Car();
			length = 1;
		}
		std::cout << "*****Car constructor used*****" << std::endl;
	}
	//for practical usage
	Train(Car add, unsigned len): length(len) {
		if (add.max) {
			try {
				stock = new Car[length];
				stock[0] = Car();
				for (unsigned i = 1; i < length; ++i)
					stock[i] = add;
			}
			catch (std::bad_alloc &ex) {
				throw ex;
			}
		}
		else {
			stock = new Car[1];
			stock[0] = Car();
			length = 1;
		}
		std::cout << "*****Car and length constructor used*****" << std::endl;
	}
	//copying
	Train(const Train &ob) :length(ob.length), stock(nullptr)
	{
		if (length) {
			try {
				stock = new Car[length];
			}
			catch (std::bad_alloc &ex) {
				throw std::exception(ex);
			}
			for (unsigned i = 1; i < length; ++i)
				stock[i] = ob.stock[i];
			std::cout << "*****Copying constructor used*****" << std::endl;
		}
	}
	//initializing
	Train& operator = (const Train& ob)
	{
		if (this != &ob) {
			delete[] stock;
			stock = nullptr;
			if ((length = ob.length) != 0) {
				try {
					stock = new Car[length];
				}
				catch (std::bad_alloc &ex) {
					throw std::exception(ex);
				}
				for (unsigned i = 0; i < length; ++i)
					stock[i] = ob.stock[i];
			}
		}
		std::cout << "*****Initializing constructor used*****" << std::endl;
		return *this;
	}
	//moving 
	Train(Train && p) : length(p.length), stock(p.stock)
	{
		p.stock = nullptr;
		std::cout << "*****Moving constructor used*****" << std::endl;
	}
	//destructor
	~Train() {
		delete[] stock;
		length = 0;
		std::cout << "*****Destructor used*****" << std::endl;
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
	friend Train operator+ (Train t1, Train t2);
	//task 9 
	Train operator ()(unsigned n, unsigned num[]);
	//task 10 +
	unsigned PassCount();
	//task 11
	friend Train operator+ (Train t1, Train t2);
	//dynamic memory
	friend Car* Realloc(Car* oldSt, unsigned oldSZ, unsigned newSZ);
	//Real Train
	//delete passengers
	void DeletePass(unsigned n, unsigned pass);

};

#endif