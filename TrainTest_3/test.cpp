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
	ASSERT_EQ(0, a1.GetLength());
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

	EXPECT_EQ("Train of 4 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\nCar #3: ( 3 / 7 )\nCar #4: ( 4 / 6 )\n", output1.str());
}

TEST(TrainSetters, AddCarsExeption1)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	std::istringstream input2("20 7 3 6 4\n");
	std::cin.rdbuf(input2.rdbuf());

	std::ostringstream output1;
	ASSERT_ANY_THROW(a1.SetTrain(std::cin));
}

TEST(TrainSetters, AddCarsExeption2)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	std::istringstream input2("3 7 3 6 4 5 5\n");
	std::cin.rdbuf(input2.rdbuf());

	std::ostringstream output1;
	ASSERT_ANY_THROW(a1.SetTrain(std::cin));
}

TEST(TakePlaces, Regular)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	a1.TakePlaces(1, 2);
	EXPECT_EQ(3, a1.GetTaken(1));
}

TEST(TakePlaces, CarOverload)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	ASSERT_ANY_THROW(a1.TakePlaces(1, 10));
	EXPECT_EQ(1, a1.GetTaken(1));
}

TEST(TakePlaces, NotExistingCar)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	ASSERT_ANY_THROW(a1.TakePlaces(5, 1));
}

TEST(AddCar, RegularCar)
{
	Train a1;
	Car added(9, 1);
	a1.AddCar(added);
	EXPECT_EQ(9, a1.GetMax(1));
	EXPECT_EQ(1, a1.GetTaken(1));
	EXPECT_EQ(1, a1.GetLength());

}
TEST(AddCar, RegularNumbers)
{
	Train a1;
	a1.AddCar(9,1);
	EXPECT_EQ(9, a1.GetMax(1));
	EXPECT_EQ(1, a1.GetTaken(1));
	EXPECT_EQ(1, a1.GetLength());
}
TEST(AddCar, Overload)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	ASSERT_ANY_THROW(a1.AddCar(9, 1));
}

TEST(Divide, Regular)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);
	unsigned arr[2] = { 1,3 };

	Train a2 = a1.Divide(2, arr);

	std::ostringstream output1;
	a1.ShowTrain(output1);
	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 2 / 8 )\nCar #2: ( 4 / 6 )\n", output1.str());
	std::ostringstream output2;
	a2.ShowTrain(output2);
	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 3 / 7 )\n", output2.str());
}

TEST(Divide, Full)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);
	unsigned arr[4] = { 1,2,3,4 };

	Train a2 = a1.Divide(4, arr);

	std::ostringstream output1;
	a1.ShowTrain(output1);
	EXPECT_EQ("That's just a locomotive\n", output1.str());
	std::ostringstream output2;
	a2.ShowTrain(output2);
	EXPECT_EQ("Train of 4 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\nCar #3: ( 3 / 7 )\nCar #4: ( 4 / 6 )\n", output2.str());
}

TEST(Divide, NoDeleted1)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);
	unsigned arr[1] = {5};

	Train a2 = a1.Divide(1, arr);

	std::ostringstream output1;
	a1.ShowTrain(output1);
	EXPECT_EQ("Train of 4 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\nCar #3: ( 3 / 7 )\nCar #4: ( 4 / 6 )\n", output1.str());
	std::ostringstream output2;
	a2.ShowTrain(output2);
	EXPECT_EQ("That's just a locomotive\n", output2.str());
}

TEST(Divide, NoDeleted2)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);
	unsigned arr[1] = { 0 };

	Train a2 = a1.Divide(0, arr);

	std::ostringstream output1;
	a1.ShowTrain(output1);
	EXPECT_EQ("Train of 4 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 2 / 8 )\nCar #3: ( 3 / 7 )\nCar #4: ( 4 / 6 )\n", output1.str());
	std::ostringstream output2;
	a2.ShowTrain(output2);
	EXPECT_EQ("That's just a locomotive\n", output2.str());
}

TEST(Divide, ExtraCars)
{
	Train a1;
	std::istringstream input1("4 9 1 8 2 7 3 6 4\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);
	unsigned arr[5] = { 10,1,5,1,3 };

	Train a2 = a1.Divide(5, arr);

	std::ostringstream output1;
	a1.ShowTrain(output1);
	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 2 / 8 )\nCar #2: ( 4 / 6 )\n", output1.str());
	std::ostringstream output2;
	a2.ShowTrain(output2);
	EXPECT_EQ("Train of 2 cars:\nCar #1: ( 1 / 9 )\nCar #2: ( 3 / 7 )\n", output2.str());
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
	a1.SetTrain(std::cin);
	EXPECT_EQ(10, a1.PassCount());
}

TEST(PassCount, Empty)
{
	Train a1;
	std::istringstream input1("4 9 0 8 0 7 0 6 0\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);
	EXPECT_EQ(0, a1.PassCount());
}