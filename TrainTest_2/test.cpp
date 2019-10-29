#include "pch.h"
#include"../TrainTask3A/Train.cpp"
//Constructor testing
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
	a1.ShowTrain(output);

	EXPECT_EQ("That's just a locomotive\n", output.str());
	ASSERT_EQ(0, a1.GetMax(0));
	ASSERT_EQ(0, a1.GetTaken(0));
}

// Setters testing

TEST(TrainSetters, Usual)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	std::ostringstream output1;
	a1.ShowTrain(output1);

	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\n", output1.str());
}

TEST(TrainSetters, Exception)
{
	Train a1;

	std::istringstream input1("20 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	ASSERT_ANY_THROW(a1.SetTrain(std::cin));
}

TEST(TrainSetters, CarError)
{
	Train a1;

	std::istringstream input1("3 9 1 8 2 3 7\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	std::ostringstream output1;
	a1.ShowTrain(output1);

	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\n", output1.str());
}

TEST(TrainSetters, Locomotive)
{
	Train a1;

	std::istringstream input1("0\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	std::ostringstream output1;
	a1.ShowTrain(output1);

	EXPECT_EQ("That's just a locomotive\n", output1.str());
}

TEST(TrainSetters, AddCars)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	std::istringstream input2("2 7 3 6 4\n");
	std::cin.rdbuf(input2.rdbuf());
	a1.SetTrain(std::cin);

	std::ostringstream output1;
	a1.ShowTrain(output1);

	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\n", output1.str());
}

