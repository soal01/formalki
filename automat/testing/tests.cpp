#include <gtest/gtest.h>
#include "main.h"


TEST(EqualTest, FirstTest) {
	Automat a;
	std::ifstream file;
	file.open("first.in");
	file >> a;
	file.clear();
	file.seekg(0);
	Automat b;
	file >> b;
	file.close();
	ASSERT_EQ(a == b, true);
}


TEST(DeterminateTest, FirstTest) {
	Automat a;
	std::ifstream file;
	file.open("second.in");
	file >> a;
	Automat b;
	file >> b;
	a = determinateAutomat(a);
	file.close();
	ASSERT_EQ(a == b, true);
}

TEST(MinimizeTest, FirstTest) {
	Automat a;
	std::ifstream file;
	file.open("third.in");
	file >> a;
	Automat b;
	file >> b;
	a = makeMinimalDeterminateAutomat(a);
	file.close();
	ASSERT_EQ(a == b, true);
}
