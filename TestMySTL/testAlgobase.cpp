#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Algobase.h"   
#include <vector>
#include <string>
#include <functional>


    TEST(AlgoBaseTest, MaxFunction) {
        EXPECT_EQ(mystl::max(3, 5), 5);
        EXPECT_EQ(mystl::max(-1, -5), -1);
        EXPECT_EQ(mystl::max(0, 0), 0);
        EXPECT_EQ(mystl::max(3.2, 2.8), 3.2);
    }

    TEST(AlgoBaseTest, MinFunction) {
        EXPECT_EQ(mystl::min(3, 5), 3);
        EXPECT_EQ(mystl::min(-1, -5), -5);
        EXPECT_EQ(mystl::min(0, 0), 0);
        EXPECT_EQ(mystl::min(3.2, 2.8), 2.8);
    }

    TEST(AlgoBaseTest, EqualFunction) {
        int arr1[] = { 1, 2, 3 };
        int arr2[] = { 1, 2, 3 };
        int arr3[] = { 1, 2, 4 };

        EXPECT_TRUE(mystl::equal(std::begin(arr1), std::end(arr1), std::begin(arr2)));
        EXPECT_FALSE(mystl::equal(std::begin(arr1), std::end(arr1), std::begin(arr3)));
    }

    TEST(AlgoBaseTest, IterSwapFunction) {
        int a = 1, b = 2;
        mystl::iter_swap(&a, &b);
        EXPECT_EQ(a, 2);
        EXPECT_EQ(b, 1);
    }

    TEST(AlgoBaseTest, CopyFunction) {
        int src[] = { 1, 2, 3, 4, 5 };
        int dest[5] = { 0 };
        mystl::copy(std::begin(src), std::end(src), std::begin(dest));
        EXPECT_TRUE(mystl::equal(std::begin(src), std::end(src), std::begin(dest)));
    }

    TEST(AlgoBaseTest, CopyBackwardFunction) {
        int src[] = { 1, 2, 3, 4, 5 };
        int dest[5] = { 0 };
        int test[] = { 1, 2, 3, 4, 5 };
        mystl::copy_backward(std::begin(src), std::end(src), std::end(dest));
        EXPECT_TRUE(std::equal(std::begin(dest), std::end(dest), std::begin(test)));
    }

    TEST(AlgoBaseTest, CopyIfFunction) {
        std::vector<int> source = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
        std::vector<int> destination;

        auto is_even = [](int num) { return num % 2 == 0; };
        mystl::copy_if(source.begin(), source.end(), std::back_inserter(destination), is_even);

        std::vector<int> expected;
        std::copy_if(source.begin(), source.end(), std::back_inserter(expected), is_even);

        EXPECT_EQ(destination, expected);
    }

    TEST(AlgoBaseTest, CopyNTest) {
        int src[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int dest[5] = { 0 };
        int test[] = { 1, 2, 3, 4, 5 };

        mystl::copy_n(std::begin(src), 5, std::begin(dest));
		EXPECT_TRUE(mystl::equal(std::begin(dest), std::end(dest), std::begin(test)));
    }

    TEST(AlgoBaseTest, MoveTest) {
        int src[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int dest[5] = { 0 };
		int test[] = { 1, 2, 3, 4, 5 };
        mystl::move(std::begin(src), std::begin(src) + 5, std::begin(dest));
		EXPECT_TRUE(mystl::equal(std::begin(dest), std::end(dest), std::begin(test)));
    }

    TEST(AlgoBaseTest, MoveBackwardTest) {
        int src[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        int dest[5] = { 0 };
        int test[] = { 1, 2, 3, 4, 5 };
        mystl::move_backward(std::begin(src), std::begin(src) + 5, std::end(dest));
        EXPECT_TRUE(mystl::equal(std::begin(dest), std::end(dest), std::begin(test)));
    }

    TEST(AlgoBaseTest, FillNTest) {
		int arr[10] = { 0 };
        mystl::fill_n(std::begin(arr), 5, 42);
		for (int i = 0; i < 5; ++i) {
			EXPECT_EQ(arr[i], 42);
		}
		for (int i = 5; i < 10; ++i) {
			EXPECT_EQ(arr[i], 0);
		}
    }

    TEST(AlgoBaseTest, FillTest) {
        int arr[10] = { 0 };
        mystl::fill(std::begin(arr), std::begin(arr)+5, 42);
        for (int i = 0; i < 5; ++i) {
            EXPECT_EQ(arr[i], 42);
        }
        for (int i = 5; i < 10; ++i) {
            EXPECT_EQ(arr[i], 0);
        }
    }

	TEST(AlgoBaseTest, LexicographicalCompareTest) {
		std::string str1 = "nmsl1";
		std::string str2 = "nms";
		std::string str3 = "nmsl2";
		std::string str4 = "nmsl1";
		EXPECT_TRUE(mystl::lexicographical_compare(str1.begin(), str1.end(), str3.begin(), str3.end()));
        EXPECT_FALSE(mystl::lexicographical_compare(str1.begin(), str1.end(), str2.begin(), str2.end()));
        EXPECT_TRUE(mystl::lexicographical_compare(str2.begin(), str2.end(), str1.begin(), str1.end()));
        EXPECT_FALSE(mystl::lexicographical_compare(str1.begin(), str1.end(), str4.begin(), str4.end()));
	}

	TEST(AlgoBaseTest, MismatchTest) {
		int arr1[] = { 1, 2, 3, 4, 5 };
		int arr2[] = { 1, 2, 0, 4, 5 };
		auto result = mystl::mismatch(std::begin(arr1), std::end(arr1), std::begin(arr2));
		EXPECT_EQ(*result.first, 3);
		EXPECT_EQ(*result.second, 0);
	}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv); 
//    ::testing::GTEST_FLAG(filter) = "AlgoBaseTest.*";
//    return RUN_ALL_TESTS();
//}
