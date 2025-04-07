#include "pch.h"
#include <algorithm>
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\HeapAlgo.h"

// ��Ҫע����ǣ�heap��ز�������������ǺϷ���
// ������벻�ǺϷ��ѣ���ô����Ϊ��Undefined Behavior
// ��ز���Ҳ�Ͳ���������
// ���� push_heap ����
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

// ���� pop_heap ����
TEST(HeapOperationsTest, PopHeapTest) {
    int arr[] = { 4, 3, 2, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);

    mystl::pop_heap(arr, arr + size);
    EXPECT_TRUE(std::is_heap(arr, arr + size - 1));
}

// ���� sort_heap ����
TEST(HeapOperationsTest, SortHeapTest) {
    int arr[] = { 4, 3, 2, 1 };
    int size = sizeof(arr) / sizeof(arr[0]);

    mystl::make_heap(arr, arr + size);
    mystl::sort_heap(arr, arr + size);
    EXPECT_TRUE(std::is_sorted(arr, arr + size));
}

// ���� make_heap ����
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
