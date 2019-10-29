#include "pch.h"
#include"../TrainTask3A/TrainVarB.cpp"

TEST(CarConstructor, DefaultConstructor)
{
	Car a1;
	ASSERT_EQ(0, a1.max);
	ASSERT_EQ(0, a1.taken);
}
TEST(CarConstructor, OneArgConstructor)
{
	Car a1(5);
	ASSERT_EQ(5, a1.max);
	ASSERT_EQ(0, a1.taken);
}
TEST(CarConstructor, BothArgsConstructor)
{
	Car a1(5, 3);
	ASSERT_EQ(5, a1.max);
	ASSERT_EQ(3, a1.taken);
}
TEST(CarConstructor, ExeptionConstructor)
{
	Car a1(5, 3);
	ASSERT_ANY_THROW(Car a1(3, 5));
}

TEST(TrainConstructor, DefaultConstructor)
{
	Train a1;
	std::ostringstream output;
	//std::cout.rdbuf(output.rdbuf());
	output << a1;

	EXPECT_EQ("That's just a locomotive\n", output.str());
	ASSERT_EQ(0, a1.GetMax(0));
	ASSERT_EQ(0, a1[0]);
	ASSERT_EQ(1, a1.GetLength());
}
TEST(TrainConstructor, CarConstructor)
{
	Car a(5, 3);
	Train a1(a);

	std::ostringstream output;
	//std::cout.rdbuf(output.rdbuf());
	output << a1;

	EXPECT_EQ("Train of 1 car:\nCar #1: ( 3 / 5 )\n", output.str());
	ASSERT_EQ(0, a1.GetMax(0));
	ASSERT_EQ(0, a1[0]);
	ASSERT_EQ(5, a1.GetMax(1));
	ASSERT_EQ(3, a1[1]);
	ASSERT_EQ(2, a1.GetLength());
}

TEST(TrainSetters, Usual)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	std::ostringstream output1;
	output1 << a1;

	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\n", output1.str());
}
TEST(TrainSetters, Exception)
{
	Train a1;

	std::istringstream input1("25 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	ASSERT_ANY_THROW(std::cin >> a1;);
}
TEST(TrainSetters, CarError)
{
	Train a1;

	std::istringstream input1("2 8 2 3 7\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	std::ostringstream output1;
	output1 << a1;

	EXPECT_EQ("Train of 1 car:\nCar #1: ( 2 / 8 )\n", output1.str());
}
TEST(TrainSetters, Locomotive)
{
	Train a1;

	std::istringstream input1("0\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	std::ostringstream output1;
	output1 << a1;

	EXPECT_EQ("That's just a locomotive\n", output1.str());
}
TEST(TrainSetters, AddCars)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	std::istringstream input2("2 7 3 6 4\n");
	std::cin.rdbuf(input2.rdbuf());
	std::cin >> a1;

	std::ostringstream output1;
	output1 << a1;

	EXPECT_EQ("Train of 4 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\nCar #3: ( 3 / 7 )\nCar #4: ( 4 / 6 )\n", output1.str());
}
TEST(TrainSetters, AddCarsExeption1)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	std::istringstream input2("20 7 3 6 4\n");
	std::cin.rdbuf(input2.rdbuf());
	
	ASSERT_ANY_THROW(std::cin >> a1);
}
TEST(TrainSetters, AddCarsExeption2)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	std::istringstream input2("5 7 3 6 4 5 5 9 0 9 0\n");
	std::cin.rdbuf(input2.rdbuf());

	ASSERT_ANY_THROW(std::cin >> a1);
}

TEST(TakePlaces, Regular)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	a1(1, 2);
	EXPECT_EQ(3, a1[1]);
}
TEST(TakePlaces, CarOverload)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	ASSERT_ANY_THROW(a1(1, 10));
	EXPECT_EQ(1, a1[1]);
}
TEST(TakePlaces, NotExistingCar)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	ASSERT_ANY_THROW(a1(5, 1));
}

TEST(AddCar, RegularCar)
{
	Train a1;
	Car added(9, 1);
	a1+=added;
	EXPECT_EQ(9, a1.GetMax(1));
	EXPECT_EQ(1, a1[1]);
	EXPECT_EQ(2, a1.GetLength());

}
TEST(AddCar, RegularNumbers)
{
	Train a1;
	a1+=Car(9, 1);
	EXPECT_EQ(9, a1.GetMax(1));
	EXPECT_EQ(1, a1[1]);
	EXPECT_EQ(2, a1.GetLength());
}
TEST(AddCar, Overload)
{
	Train a1;
	std::istringstream input1("5 9 1 8 2 7 3 6 4 5 5\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;

	ASSERT_ANY_THROW(a1+=Car(9, 1));
}

TEST(Divide, Regular)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;
	unsigned arr[2] = { 1,3 };

	Train a2 = a1(2, arr);

	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 2 / 8 )\nCar #2: ( 4 / 6 )\n", output1.str());
	std::ostringstream output2;
	output2 << a2;
	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 3 / 7 )\n", output2.str());
}
TEST(Divide, Full)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;
	unsigned arr[4] = { 1,2,3,4 };

	Train a2 = a1(4, arr);

	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("That's just a locomotive\n", output1.str());
	std::ostringstream output2;
	output2 << a2;
	EXPECT_EQ("Train of 4 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\nCar #3: ( 3 / 7 )\nCar #4: ( 4 / 6 )\n", output2.str());
}
TEST(Divide, NoDeleted1)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;
	unsigned arr[1] = { 5 };

	Train a2 = a1(1, arr);

	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("Train of 4 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\nCar #3: ( 3 / 7 )\nCar #4: ( 4 / 6 )\n", output1.str());
	std::ostringstream output2;
	output2 << a2;
	EXPECT_EQ("That's just a locomotive\n", output2.str());
}
TEST(Divide, NoDeleted2)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;
	unsigned arr[1] = { 0 };

	Train a2 = a1(0, arr);

	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("Train of 4 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\nCar #3: ( 3 / 7 )\nCar #4: ( 4 / 6 )\n", output1.str());
	std::ostringstream output2;
	output2 << a2;
	EXPECT_EQ("That's just a locomotive\n", output2.str());
}
TEST(Divide, ExtraCars)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;
	unsigned arr[5] = { 10,1,5,1,3 };
	EXPECT_ANY_THROW(a1(5, arr));
}
TEST(Divide, TooBigArray)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;
	unsigned arr[10] = { 0,1,2,3,4,5,6,7,8,9 };

	EXPECT_ANY_THROW(a1(10, arr));
}

TEST(PassCount, Loco)
{
	Train a1;
	EXPECT_EQ(0, a1.PassCount());
}
TEST(PassCount, Regular)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;
	EXPECT_EQ(10, a1.PassCount());
}
TEST(PassCount, Empty)
{
	Train a1;
	std::istringstream input1("4 9 0 8 0 7 0 6 0\n");
	std::cin.rdbuf(input1.rdbuf());
	std::cin >> a1;
	EXPECT_EQ(0, a1.PassCount());
}

TEST(PlusOperator, TrainPLCar)
{
	Train a1(Car(1,1));
	Car c1(2, 2);
	a1 = a1 + c1;
	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 1 )\nCar #2: ( 2 / 2 )\n", output1.str());
}
TEST(PlusOperator, TrainPLTrain)
{
	Train a1(Car(1, 1));
	Train a2(Car(2, 2));
	a1 = a1 + a2;
	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 1 )\nCar #2: ( 2 / 2 )\n", output1.str());
}
TEST(PlusOperator, LocoPLCar)
{
	Train a1;
	Car c1(2, 2);
	a1 = a1 + c1;
	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("Train of 1 car:\nCar #1: ( 2 / 2 )\n", output1.str());
}
TEST(PlusOperator, LocoPLTrain)
{
	Train a1;
	Train c1(Car(2, 2));
	a1 = a1 + c1;
	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("Train of 1 car:\nCar #1: ( 2 / 2 )\n", output1.str());
}
TEST(PlusOperator, Combination)
{
	Train a1;
	Car c1(2, 2), c2(1, 1);
	Train a2 = Train(c1) + Train(Car(3, 3));
	a1 =  a2 + c2 + a2;
	std::ostringstream output1;
	output1 << a1;
	EXPECT_EQ("Train of 5 cars:\nCar #1: ( 2 / 2 )\nCar #2: ( 3 / 3 )\nCar #3: ( 1 / 1 )\nCar #4: ( 2 / 2 )\nCar #5: ( 3 / 3 )\n", output1.str());
}
TEST(PlusOperator, LocoPLLoco)
{
	Train a1;
	Car c1;
	EXPECT_ANY_THROW(a1 = a1 + c1);
}
TEST(PlusOperator, TrainPLLoco)
{
	Train a1 (Car(1,1)) ;
	Car c1;
	EXPECT_ANY_THROW(a1 = a1 + c1);
}
TEST(PlusOperator, Overload)
{
	Car c1(2, 2);
	Train a1 (Car(1,1)), a2 = a1 + c1 + Car(3,3);

	EXPECT_ANY_THROW(a1 = a1 + a2 + c1 + a2);
}
