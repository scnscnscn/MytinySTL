#include "pch.h"
#include <algorithm>
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\HeapAlgo.h"

// 需要注意的是，heap相关操作会假设输入是合法堆
// 如果输入不是合法堆，那么该行为是Undefined Behavior
// 相关操作也就不再有意义
// 测试 push_heap 函数
TEST(HeapOperationsTest, PushHeapTest) {
    int arr[] = { 1, 2, 3 };
    int size = sizeof(arr) / sizeof(arr[0]);

    int* newArr = new int[size + 1];
    std::copy(arr, arr + size, newArr);
    std::make_heap(newArr, newArr + size);

    newArr[size] = 4;
    mystl::push_heap(newArr, newArr + size + 1);

    EXPECT_TRUE(std::is_heap(newArr, newArr + size + 1));
	EXPECT_EQ(newArr[0], 4); 
    delete[] newArr;

}

// 测试 pop_heap 函数
TEST(HeapOperationsTest, PopHeapTest) {
    int arr[] = { 4, 3, 2, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);

    mystl::pop_heap(arr, arr + size);
    EXPECT_TRUE(std::is_heap(arr, arr + size - 1));
}

// 测试 sort_heap 函数
TEST(HeapOperationsTest, SortHeapTest) {
    int arr[] = { 4, 3, 2, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);

    mystl::make_heap(arr, arr + size);
    mystl::sort_heap(arr, arr + size);
    EXPECT_TRUE(std::is_sorted(arr, arr + size));
}

// 测试 make_heap 函数
TEST(HeapOperationsTest, MakeHeapTest) {
    int arr[] = { 4, 3, 2, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);

    mystl::make_heap(arr, arr + size);
    EXPECT_TRUE(std::is_heap(arr, arr + size));
}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "HeapOperationsTest.*";
//    return RUN_ALL_TESTS();
//}
