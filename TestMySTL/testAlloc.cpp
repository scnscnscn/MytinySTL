#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Alloc.h" 

// 测试 allocate 方法
TEST(AllocTest, AllocateTest) {
    size_t smallSize = 10;
    size_t largeSize = 5000;

    // 测试小内存分配
    void* smallPtr = mystl::alloc::allocate(smallSize);
    EXPECT_NE(smallPtr, nullptr);

    // 测试大内存分配
    void* largePtr = mystl::alloc::allocate(largeSize);
    EXPECT_NE(largePtr, nullptr);

    // 释放内存
    mystl::alloc::deallocate(smallPtr, smallSize);
    mystl::alloc::deallocate(largePtr, largeSize);
}

// 测试 deallocate 方法
TEST(AllocTest, DeallocateTest) {
    size_t size = 20;
    void* ptr = mystl::alloc::allocate(size);
    EXPECT_NE(ptr, nullptr);

    // 释放内存
    mystl::alloc::deallocate(ptr, size);
    // 这里无法直接验证内存是否正确释放，只是验证流程
}

// 测试 reallocate 方法
TEST(AllocTest, ReallocateTest) {
    size_t oldSize = 15;
    size_t newSize = 30;

    void* oldPtr = mystl::alloc::allocate(oldSize);
    EXPECT_NE(oldPtr, nullptr);

    void* newPtr = mystl::alloc::reallocate(oldPtr, oldSize, newSize);
    EXPECT_NE(newPtr, nullptr);

    // 释放内存
    mystl::alloc::deallocate(newPtr, newSize);
}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "AllocTest.*";
//    return RUN_ALL_TESTS();
//}
