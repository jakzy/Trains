#include "pch.h"
//#include"../TrainTask3A/Train.h"
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
	Car a1(5,3);
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

TEST(TrainMethods, Setters_2)
{
	Train a1;

	std::istringstream input1("2 9 1 8 2\n");
	std::cin.rdbuf(input1.rdbuf());
	a1.SetTrain(std::cin);

	std::ostringstream output1;
	a1.ShowTrain(output1);

	EXPECT_EQ("\n", output1.str());
}
/*
TEST(StrophoidMethods, Coordinates)
{
	Strophoid a1; // A=1 O(0,0)
	ASSERT_EQ(0, a1.Coordinate(-1).x);
	ASSERT_EQ(0, a1.Coordinate(-1).y);
	ASSERT_EQ(0, a1.Coordinate(0).x);
	ASSERT_EQ(0, a1.Coordinate(0).y);
	ASSERT_EQ(0.3, a1.Coordinate(-0.6).x);
	ASSERT_EQ(-0.3, a1.Coordinate(-0.6).y);
	ASSERT_ANY_THROW(a1.Coordinate(2));
}
TEST(StrophoidMethods, Methods)
{
	Strophoid a1; // A=1 O(0,0)
	ASSERT_EQ(abs(cos(2) / cos(1)), a1.PolarRad(1, 0));
	ASSERT_ANY_THROW(a1.PolarRad(90, 1));

	ASSERT_EQ(sqrt(2), a1.CurveRad());
	ASSERT_EQ(2 - 0.5*PI, a1.LoopArea());
	ASSERT_EQ(PI*(2 * log(2) - 4 / 3), a1.LoopVolume());
	ASSERT_EQ((2 + 0.5*PI), a1.AsympArea());

	Strophoid a2(2, Point(4, 5)); //Point doesnt matter here
	ASSERT_EQ(2 * sqrt(2), a2.CurveRad());
	ASSERT_EQ(4 * (2 - 0.5*PI), a2.LoopArea());
	ASSERT_EQ(PI * 8 * (2 * log(2) - 4 / 3), a2.LoopVolume());
	ASSERT_EQ(4 * (2 + 0.5*PI), a2.AsympArea());
}*/