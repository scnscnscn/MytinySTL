#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Numeric.h"
#include <vector>
#include <functional>

TEST(NumericTest, Accumulate) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    int result = mystl::accumulate(vec.begin(), vec.end(), 0);
    EXPECT_EQ(result, 15);

    result = mystl::accumulate(vec.begin(), vec.end(), 10);
    EXPECT_EQ(result, 25);
}

TEST(NumericTest, AccumulateWithBinaryOp) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    int result = mystl::accumulate(vec.begin(), vec.end(), 1, std::multiplies<int>());
    EXPECT_EQ(result, 120);
}

TEST(NumericTest, AdjacentDifference) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::vector<int> result(vec.size());
    mystl::adjacent_difference(vec.begin(), vec.end(), result.begin());
    std::vector<int> expected = { 1, 1, 1, 1, 1 };
    EXPECT_EQ(result, expected);
}

TEST(NumericTest, AdjacentDifferenceWithBinaryOp) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::vector<int> result(vec.size());
    mystl::adjacent_difference(vec.begin(), vec.end(), result.begin(), std::plus<int>());
    std::vector<int> expected = { 1, 3, 5, 7, 9 };
    EXPECT_EQ(result, expected);
}

TEST(NumericTest, InnerProduct) {
    std::vector<int> vec1 = { 1, 2, 3, 4, 5 };
    std::vector<int> vec2 = { 5, 4, 3, 2, 1 };
    int result = mystl::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0);
    EXPECT_EQ(result, 35);
}

TEST(NumericTest, InnerProductWithBinaryOp) {
    std::vector<int> vec1 = { 1, 2, 3, 4, 5 };
    std::vector<int> vec2 = { 5, 4, 3, 2, 1 };
    int result = mystl::inner_product(vec1.begin(), vec1.end(), vec2.begin(), 0, std::plus<int>(), std::multiplies<int>());
    EXPECT_EQ(result, 35);
}

TEST(NumericTest, Iota) {
    std::vector<int> vec(5);
    mystl::iota(vec.begin(), vec.end(), 10);
    std::vector<int> expected = { 10, 11, 12, 13, 14 };
    EXPECT_EQ(vec, expected);
}

TEST(NumericTest, PartialSum) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::vector<int> result(vec.size());
    mystl::partial_sum(vec.begin(), vec.end(), result.begin());
    std::vector<int> expected = { 1, 3, 6, 10, 15 };
    EXPECT_EQ(result, expected);
}

TEST(NumericTest, PartialSumWithBinaryOp) {
    std::vector<int> vec = { 1, 2, 3, 4, 5 };
    std::vector<int> result(vec.size());
    mystl::partial_sum(vec.begin(), vec.end(), result.begin(), std::multiplies<int>());
    std::vector<int> expected = { 1, 2, 6, 24, 120 };
    EXPECT_EQ(result, expected);
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv); 
    ::testing::GTEST_FLAG(filter) = "NumericTest.*";
    return RUN_ALL_TESTS();
}
