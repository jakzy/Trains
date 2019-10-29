#include "pch.h"
#include <iostream>
#include "Train.h"

const char* MENU[]{ "1. Create an empty car", "2. Create a car", "3. Create a locomotive", "4. Create a train",
"5. Show train", "6. Take seats in the car", "7. Show taken seats in the car", "8. Add the car to the train",
"9. Divide your train into two", "10. Show amount of passengers in the train", "0. Exit" };
const unsigned menuSZ = sizeof(MENU) / sizeof(MENU[0]);

int main()
{
	unsigned menu = 1, 
			 n,pass,
			 max0, taken0;
	Train train;
	Car newCar;
	Car carArr[MAX_LENGTH];
	const char*errmsg = "";
	bool work = true;
	std::cout << "Maximum train size: locomotive + " << MAX_LENGTH-1 << " cars" << std::endl;
	do {
		if (menu)
			for (size_t i = 0; i != menuSZ; ++i)
				std::cout << MENU[i] << std::endl;
		menu = GetNum(">>");
		switch (menu)
		{
		case 0:
			work = false;
			break;
		case 1:
			newCar = Car();
			std::cout << "You created a locomotive car: ( " << newCar.taken << " / " << newCar.max << " )" << std::endl;
			break;
		case 2:
			max0 = GetNum("Seats: ");
			taken0 = GetNum("Taken seats: ");
			try {
				newCar = Car(max0, taken0);
				std::cout << "You created a new car: ( " << newCar.taken << " / " << newCar.max << " )" << std::endl;
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		case 3:
			train = Train();
			break;
		case 4:
			try { train.SetTrain(std::cin); }
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		case 5:
			train.ShowTrain(std::cout);
			break;
		case 6:
			n = GetNum("Number of the car:");
			pass = GetNum("New passengers: ");
			try {
				train.TakePlaces(n, pass);
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		case 7:
			n = GetNum("Number of the car:");
			try {
				std::cout << "Taken seats in car #" << n << ": " << train.GetTaken(n) << std::endl;
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		case 8:
			try {
				if (newCar.max) {
					try {
						train.AddCar(newCar);
						newCar = Car();
					}
					catch (std::exception &ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				else {
					try {
						train.AddCar(GetNum("Seats: "), GetNum("Taken seats: "));
					}
					catch (std::exception &ex)
					{
						std::cout << ex.what() << std::endl;
					}
				}
				std::cout << "You succesfully added a new car to the train!" << std::endl;
			}
			catch (std::exception &ex)
			{
				std::cout << ex.what() << std::endl;
			}
			break;
		case 9:
			unsigned arr[MAX_LENGTH];
			n = GetNum("Enter amount of cars to unrivet:");
			std::cout << "Enter numbers of cars to unrivet:"<<std::endl;
			for (unsigned i = 0; i < n; ++i)
				arr[i] = GetNum(">>");
			train.Divide(n, arr).ShowTrain(std::cout);
			break;
		case 10:
			std::cout << "Amount of passengers in the train: "<< train.PassCount() << std::endl;
			break;
		default:
			std::cout << "Enter error, try again" << std::endl;
			break;
		}
		if (menu) {
			std::cout << "Enter 0 to continue, 1 to show the menu once again, ctrl+z to leave" << std::endl;
			do {
				std::cout << ">>";
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				std::cin >> menu;
				if (std::cin.eof())
					work = false;
				else {
					if (!(std::cin.good()))
						std::cout << "Enter error, try again" << std::endl;
				}
			} while ((work) && !(std::cin.good()));
		}
	} while (work);
}