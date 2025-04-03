#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Allocator.h"

// 简单的测试类，用于测试 allocator 的功能
class TestClass {
public:
    TestClass() : value(0) {}
    TestClass(int val) : value(val) {}
    ~TestClass() {}
    int value;
};

// 测试 allocate 和 deallocate 方法
TEST(AllocatorTest, AllocateAndDeallocate) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    EXPECT_NE(ptr, nullptr);
    alloc.deallocate(ptr);
}

// 测试 allocate 带参数的方法
TEST(AllocatorTest, AllocateWithSize) {
    mystl::allocator<TestClass> alloc;
    size_t n = 5;
    TestClass* ptr = alloc.allocate(n);
    EXPECT_NE(ptr, nullptr);
    alloc.deallocate(ptr, n);
}

// 测试 construct 无参数的方法
TEST(AllocatorTest, ConstructDefault) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    alloc.construct(ptr);
    EXPECT_EQ(ptr->value, 0);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// 测试 construct 带参数的方法
TEST(AllocatorTest, ConstructWithValue) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    TestClass value(42);
    alloc.construct(ptr, value);
    EXPECT_EQ(ptr->value, 42);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// 测试 construct 带右值引用参数的方法
TEST(AllocatorTest, ConstructWithRValue) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    alloc.construct(ptr, TestClass(42));
    EXPECT_EQ(ptr->value, 42);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// 测试 construct 带可变参数模板的方法
TEST(AllocatorTest, ConstructWithArgs) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    alloc.construct(ptr, 42);
    EXPECT_EQ(ptr->value, 42);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// 测试 destroy 单个对象的方法
TEST(AllocatorTest, DestroySingle) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    alloc.construct(ptr);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// 测试 destroy 多个对象的方法
TEST(AllocatorTest, DestroyRange) {
    mystl::allocator<TestClass> alloc;
    size_t n = 5;
    TestClass* first = alloc.allocate(n);
    for (size_t i = 0; i < n; ++i) {
        alloc.construct(first + i, static_cast<int>(i));
    }
    alloc.destroy(first, first + n);
    alloc.deallocate(first, n);
}

//int main(int argc, char **argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "AllocatorTest.*";
//    return RUN_ALL_TESTS();
//}    