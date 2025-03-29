#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Alloc.h" 

// ���� allocate ����
TEST(AllocTest, AllocateTest) {
    size_t smallSize = 10;
    size_t largeSize = 5000;

    // ����С�ڴ����
    void* smallPtr = mystl::alloc::allocate(smallSize);
    EXPECT_NE(smallPtr, nullptr);

    // ���Դ��ڴ����
    void* largePtr = mystl::alloc::allocate(largeSize);
    EXPECT_NE(largePtr, nullptr);

    // �ͷ��ڴ�
    mystl::alloc::deallocate(smallPtr, smallSize);
    mystl::alloc::deallocate(largePtr, largeSize);
}

// ���� deallocate ����
TEST(AllocTest, DeallocateTest) {
    size_t size = 20;
    void* ptr = mystl::alloc::allocate(size);
    EXPECT_NE(ptr, nullptr);

    // �ͷ��ڴ�
    mystl::alloc::deallocate(ptr, size);
    // �����޷�ֱ����֤�ڴ��Ƿ���ȷ�ͷţ�ֻ����֤����
}

// ���� reallocate ����
TEST(AllocTest, ReallocateTest) {
    size_t oldSize = 15;
    size_t newSize = 30;

    void* oldPtr = mystl::alloc::allocate(oldSize);
    EXPECT_NE(oldPtr, nullptr);

    void* newPtr = mystl::alloc::reallocate(oldPtr, oldSize, newSize);
    EXPECT_NE(newPtr, nullptr);

    // �ͷ��ڴ�
    mystl::alloc::deallocate(newPtr, newSize);
}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "AllocTest.*";
//    return RUN_ALL_TESTS();
//}
