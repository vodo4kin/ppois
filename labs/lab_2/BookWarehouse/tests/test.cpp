#include <gtest/gtest.h>

TEST(ExampleTest, BasicTest) {
    EXPECT_EQ(2 + 2, 4);
}

TEST(ExampleTest, StringTest) {
    std::string hello = "hello";
    EXPECT_EQ(hello, "hello");
}

int main(int argc, char **argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
