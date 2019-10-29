#include "pch.h"
#include "TrainVarC.h"


	const char* MENU[]{ "0. Go to the next station","1. Show train", "2. Take seats in the car", 
		"3. Delete passengers from the car", "4. Show taken seats in the car",  "5. Show amount of passengers in the train", 
		"***Press any other number to leave***"};
	const unsigned menuSZ = sizeof(MENU) / sizeof(MENU[0]);

	int main()
	{
		unsigned menu = 1,
			n, pass, max;
		const char*errmsg = "";
		bool work = true;

		//create a train
		n = GetNum("Enter length of your train (with locomotive):");
		max = GetNum("Possible amount of passengers in 1 car:");
		Train train(Car(max), n);

		do {
			if (menu)
				for (size_t i = 0; i != menuSZ; ++i)
					std::cout << MENU[i] << std::endl;
			menu = GetNum(">>");
			switch (menu)
			{
			case 0: //passengers in and out
				//random
				srand(NULL);
				for (unsigned i = 1; i < n; ++i) {
					pass = rand() % max;
					try {
						train.DeletePass(i, pass);
						std::cout << pass << ((pass == 1) ? " passenger" : " passengers")<<" came out of the car #" << i << std::endl;
					}
					catch (std::exception){
						std::cout << "No passengers came out of car #" << i << std::endl;
					}
					pass = rand() % max;
					try {
						train(i, pass);
						std::cout << pass << ((pass == 1) ? " passenger" : " passengers") << " came into the car #" << i << std::endl;
					}
					catch (std::exception) {
						std::cout << "No passengers came into the car #" << i << std::endl;
					}
					std::cout << std::endl;
				}
				break;
			case 1: //show train
				std::cout << train;
				break;
			case 2: //add passengers to the car
				n = GetNum("Number of the car:");
				pass = GetNum("New passengers: ");
				try {
					train(n, pass);
				}
				catch (std::exception &ex)
				{
					std::cout << ex.what() << std::endl;
				}
				break;
			case 3: //delete passengers from the car
				n = GetNum("Number of the car:");
				pass = GetNum("Amount of leaving passengers: ");
				try {
					train.DeletePass(n, pass);
				}
				catch (std::exception &ex)
				{
					std::cout << ex.what() << std::endl;
				}
				break;
			case 4: //show the passengers in the exact car
				n = GetNum("Number of the car:");
				try {
					std::cout << "Taken seats in car #" << n << ": " << train[n] << std::endl;
				}
				catch (std::exception &ex)
				{
					std::cout << ex.what() << std::endl;
				}
				break;
			case 5: //full train
				std::cout << "Amount of passengers in the train: " << train.PassCount() << std::endl;
				break;
			default:
				work = false;
				break;
			}
			if (work) {
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