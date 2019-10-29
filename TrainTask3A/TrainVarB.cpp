#include "pch.h"
#include <iostream>
#include"TrainVarB.h"

//task 4 
std::istream& operator >>(std::istream& s, Train &a)
{
	unsigned add = GetNum("Enter amount of cars: ", s);
	if ((add + 1 > MAX_LENGTH) || ((a.length + add) > MAX_LENGTH))
		throw std::exception("You can't add all the cars to this train");
	for (unsigned i = 1; i <= add; ++i) {
		std::cout << "Car #" << i << ":";
		unsigned max0 = GetNum("Seats: ", s);
		unsigned taken0 = GetNum("Taken seats: ", s);
		try {
			a.stock[a.length++] = Car(max0, taken0);
		}
		catch (std::exception &ex)
		{
			std::cout << ex.what() << std::endl;
			break;
		}
	}
	return s;
}
//task 5 +
std::ostream& operator <<(std::ostream& s, const Train &a) {
	
	if (a.length-1) {
		s << "Train of " << a.length-1 << (a.length-1 == 1 ? " car:" : " cars:") << std::endl;
		for (unsigned i = 1; i < a.length; ++i)
			s << "Car #" << i << ": ( " << a.stock[i].taken << " / " << a.stock[i].max << " )" << std::endl;
	}
	else s << "That's just a locomotive" << std::endl;
	return s;

}
//task 6 +
void Train::operator()(unsigned n, unsigned pass) {
	if (n >= length)
		throw std::exception("This car doesnt exist");
	else {
		if (pass + stock[n].taken > stock[n].max)
			throw std::exception("Can't add all the passengers to this car");
		else
			stock[n].taken += pass;
	}
}
//task 7 +
const unsigned& Train::operator [](unsigned n) const {
	if (n >= length)
		throw std::exception("This car doesn't exist");
	else
		return stock[n].taken;
}
unsigned& Train::operator [](unsigned n)  {
	if (n >= length)
		throw std::exception("This car doesn't exist");
	else
		return stock[n].taken;
}
unsigned Train::GetMax(unsigned n) const {
	if (n >= length)
		throw std::exception("This car doesn't exist");
	else
		return stock[n].max;
}
unsigned Train::GetLength() const {
	return length;
}
//task 8 +
Train& Train::operator +=(Train added) {
	if (length + added.length - 1 > MAX_LENGTH)
		throw std::exception("You can't create such a train (too long)");
	else
		if (added.length == 1)
			throw std::exception("You can't add a locomotive to a train");
		else {
			for (unsigned k = 1; k < added.length; ++k)
				stock[length++] = added.stock[k];
			return *this;
		}
}
//task 9
Train Train:: operator()(unsigned n, unsigned num[]) {
	//array sort
	if (n >= length)
		throw std::exception("You can't take that amount of cars");

	bool b = true;
	unsigned r = n;
	while (b) {
		b = false;
		for (unsigned i = 0; i + 1 < r; i++) {
			if (num[i] > num[i + 1]) {
				Swap(num[i], num[i + 1]);
				b = true;
			}
		}
		r--;
	}
	//main part
	Train deleted;
	unsigned j = 0, k = 1;
	while ((j < n) && (num[j] < length)) {
		if (stock[num[j]].max != 0) {
			deleted.stock[k++] = stock[num[j]];
			stock[num[j]] = Car();
		}
		++j;
	}
	deleted.length = k;
	k = 1;
	j = 1;
	while (k <= length) {
		if (stock[k].max)
			stock[j++] = stock[k];
		++k;
	}
	length = j;
	return deleted;
}
//task 10 +
unsigned Train::PassCount() {
	unsigned res = 0;
	for (unsigned i = 0; i <= length; ++i)
		res += stock[i].taken;
	return res;
}

//task 11
Train operator+ (Train t1, Train t2) {
	try {
		Train new_train = t1;
		new_train += t2;
		return new_train;
	}
	catch (std::exception &ex) {
		throw std::exception(ex);
	}
}

unsigned GetNum(const char* msg) {
	unsigned n;
	const char* errmsg = "";
	do {
		std::cout << errmsg << std::endl;
		std::cout << msg;
		std::cin >> n;
		if (!(std::cin.good())) {
			errmsg = "Invalid value, try again\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else return n;
	} while (true);
}

unsigned GetNum(const char* msg, std::istream& i) {
	unsigned n;
	const char* errmsg = "";
	do {
		std::cout << errmsg << std::endl;
		std::cout << msg;
		i >> n;
		if (!(std::cin.good())) {
			errmsg = "Invalid value, try again\n";
			std::cin.clear();
			std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			continue;
		}
		else return n;
	} while (true);
}

void Swap(unsigned &a, unsigned &b) {
	unsigned c;
	c = a; a = b; b = c;
}