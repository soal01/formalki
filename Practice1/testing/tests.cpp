#include <gtest/gtest.h>
#include "main.h"


TEST(RegularHandlerTests, readInputTest) {
    RegularHandler a;
    RegularHandler b("ab + c.aba. ∗ .bac. + . + ∗ ", 'b', 2);
    std::ifstream file;
    file.open("../testing/1.in");
	a.readInput(file);
    file.close();
	ASSERT_EQ(a == b, true);
}

TEST(RegularHandlerTests, EqualTest) {
    RegularHandler a("aa +", 'b', 2);
    RegularHandler b("aa +", 'b', 2);
    ASSERT_EQ(a == b, true);
}

TEST(RegularHandlerTests, FirstGetAnswerTest) {
    RegularHandler a;
    std::ifstream file;
    file.open("../testing/samples1.in");
	a.readInput(file);
    file.close();
    size_t ans = a.getAnswer();
    std::cout << ans << std::endl;
	ASSERT_EQ(ans == 4, true);
}

TEST(RegularHandlerTests, SecondGetAnswerTest) {
    RegularHandler a;
    std::ifstream file;
    file.open("../testing/samples2.in");
	a.readInput(file);
    file.close();
    size_t ans = a.getAnswer();
    std::cout << ans << std::endl;
	ASSERT_EQ(ans == 7, true);
}

TEST(RegularHandlerTests, ThirdGetAnswerTest) {
    RegularHandler a;
    std::ifstream file;
    file.open("../testing/samples3.in");
	a.readInput(file);
    file.close();
    size_t ans = a.getAnswer();
    std::cout << ans << std::endl;
	ASSERT_EQ(ans == 2, true);
}

TEST(LengthStorageTests, EqualTest) {
    LengthStorage a({1, 1, 1}, 'b');
    LengthStorage b({1, 1, 1}, 'b');

    ASSERT_EQ(a == b, true);
}

TEST(LengthStorageTests, SimpleConstructorTest) {
    LengthStorage a({1, INF, INF}, 'b');
    LengthStorage b(2, 'a', 'b');
    ASSERT_EQ(a == b, true);
}

TEST(LengthStorageTests, ConcatenateTest) {
    LengthStorage a({1, INF, INF}, 'b');
    LengthStorage b({INF, 1, INF}, 'b');
    LengthStorage c = concatenate(a, b);
    LengthStorage ans({INF, 2, INF}, 'b');
    ASSERT_EQ(c == ans, true);
}


TEST(LengthStorageTests, AddTest) {
    LengthStorage a({1, INF, INF}, 'b');
    LengthStorage b({INF, 1, INF}, 'b');
    LengthStorage c = add(a, b);
    LengthStorage ans({1, 1, INF}, 'b');
    ASSERT_EQ(c == ans, true);
}


TEST(LengthStorageTests, KleenieStarTest) {
    LengthStorage a({INF, 2, INF}, 'a');
    LengthStorage c = kleenieStar(a);
    LengthStorage ans({0, 2, 4}, 'a');
    ASSERT_EQ(c == ans, true);
}

