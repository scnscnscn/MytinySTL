#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\SetAlgo.h" 

TEST(SetAlgoTest, testSetUnion) {
    int v1[] = { 1, 3, 5 };
    int v2[] = { 2, 3, 4 };
    int result[5] = { 0 };
    auto end = mystl::set_union(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::begin(result));
    int resultSize = std::distance(std::begin(result), end);
    int expected[] = { 1, 2, 3, 4, 5 };
    EXPECT_TRUE(std::equal(result, result + resultSize, expected));
}

TEST(SetAlgoTest, testSetIntersection) {
    int v1[] = { 1, 3, 5 };
    int v2[] = { 2, 3, 4 };
    int result[1] = { 0 };
    auto end = mystl::set_intersection(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::begin(result));
    int resultSize = std::distance(std::begin(result), end);
    int expected[] = { 3 };
    EXPECT_TRUE(std::equal(result, result + resultSize, expected));
}

TEST(SetAlgoTest, testSetSymmetricDifference) {
    int v1[] = { 1, 3, 5 };
    int v2[] = { 2, 3, 4 };
    int result[4] = { 0 };
    auto end = mystl::set_symmetric_difference(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::begin(result));
    int resultSize = std::distance(std::begin(result), end);
    int expected[] = { 1, 2, 4, 5 };
    EXPECT_TRUE(std::equal(result, result + resultSize, expected));
}

TEST(SetAlgoTest, testSetDifference) {
    int v1[] = { 1, 3, 5 };
    int v2[] = { 2, 3, 4 };
    int result[2] = { 0 };
    auto end = mystl::set_difference(std::begin(v1), std::end(v1), std::begin(v2), std::end(v2), std::begin(result));
    int resultSize = std::distance(std::begin(result), end);
    int expected[] = { 1, 5 };
    EXPECT_TRUE(std::equal(result, result + resultSize, expected));
}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "SetAlgoTest.*";
//    return RUN_ALL_TESTS();
//}