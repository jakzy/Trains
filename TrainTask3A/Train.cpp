#include "pch.h"
#include <iostream>
#include"Train.h"

	//task 4 (если не можем добавить все вагоны в поезд, не добавлять вообщe)
	std::istream& Train::SetTrain(std::istream& s) 
	{
		unsigned add = GetNum("Enter amount of cars: ", s);
		if ((add >= MAX_LENGTH) || ((length + add) >= MAX_LENGTH))
			throw std::exception("You can't add all the cars to this train");
		for (unsigned i = 1; i <= add; ++i) {
			std::cout << "Car #" << i << ":";
			unsigned max0 = GetNum("Seats: ", s);
			unsigned taken0 = GetNum("Taken seats: ", s);
			try {
				stock[++length] = Car(max0, taken0);
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
				length--;
				break;
			}
		}
		return s;
	}
	//task 5 +
	std::ostream& Train::ShowTrain(std::ostream& s) {
		if (length) {
			s << "Train of " << length << (length == 1 ? " car:" : " cars:") << std::endl;
			for (unsigned i = 1; i <= length; ++i)
				s << "Car #" << i << ": ( " << stock[i].taken << " / " << stock[i].max << " )" << std::endl;
		}
		else s << "That's just a locomotive" << std::endl;
		return s;

	}
	//task 6 +
	void Train::TakePlaces(unsigned n, unsigned pass) {
		if (n > length)
			throw std::exception("This car doesnt exist");
		else {
			if (pass + stock[n].taken > stock[n].max)
				throw std::exception("Can't add all the passengers to this car");
			else
				stock[n].taken += pass;
		}
	}
	//task 7 +
	unsigned Train::GetTaken(unsigned n) const {
		if (n > length)
			throw std::exception("This car doesn't exist");
		else
			return stock[n].taken;
	}
	unsigned Train::GetMax(unsigned n) const {
		if (n > length)
			throw std::exception("This car doesn't exist");
		else
			return stock[n].max;
	}
	unsigned Train::GetLength() const {
		return length;
	}
	//task 8 (do we need to reload this function?) +
	Train Train::AddCar(unsigned max0, unsigned taken0) {
		if (taken0 > max0)
			throw std::exception("This car can't exist");
		if (length+1 < MAX_LENGTH) { // with passengers+loco, 31 pass and 1 loco max
			stock[++length].max = max0;
			stock[length].taken = taken0;
		}
		else
			throw std::exception("Train has max possible amount of cars");
	}
	Train Train::AddCar(Car added) {
		if (length+1 < MAX_LENGTH) { //32 with passengers+loco, 31 pass and 1 loco max
			stock[++length] = added;
		}
		else
			throw std::exception("Train has max possible amount of cars");
	}
	//task 9
	Train Train::Divide(unsigned n, unsigned num[]) {

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
		Train deleted;
		unsigned j = 0, k = 0;
		if (n > length)
			n = length;
		while ((j<=n)&&(num[j]<=length)) {
			if (stock[num[j]].max != 0) {
				deleted.stock[++k] = stock[num[j]];
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
		length = j-1;
		return deleted;
	}
	//task 10 +
	unsigned Train::PassCount() {
		unsigned res = 0;
		for (unsigned i = 0; i <= length; ++i)
			res += stock[i].taken;
		return res;
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
