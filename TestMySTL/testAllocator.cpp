#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Allocator.h"

// �򵥵Ĳ����࣬���ڲ��� allocator �Ĺ���
class TestClass {
public:
    TestClass() : value(0) {}
    TestClass(int val) : value(val) {}
    ~TestClass() {}
    int value;
};

// ���� allocate �� deallocate ����
TEST(AllocatorTest, AllocateAndDeallocate) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    EXPECT_NE(ptr, nullptr);
    alloc.deallocate(ptr);
}

// ���� allocate �������ķ���
TEST(AllocatorTest, AllocateWithSize) {
    mystl::allocator<TestClass> alloc;
    size_t n = 5;
    TestClass* ptr = alloc.allocate(n);
    EXPECT_NE(ptr, nullptr);
    alloc.deallocate(ptr, n);
}

// ���� construct �޲����ķ���
TEST(AllocatorTest, ConstructDefault) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    alloc.construct(ptr);
    EXPECT_EQ(ptr->value, 0);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// ���� construct �������ķ���
TEST(AllocatorTest, ConstructWithValue) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    TestClass value(42);
    alloc.construct(ptr, value);
    EXPECT_EQ(ptr->value, 42);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// ���� construct ����ֵ���ò����ķ���
TEST(AllocatorTest, ConstructWithRValue) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    alloc.construct(ptr, TestClass(42));
    EXPECT_EQ(ptr->value, 42);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// ���� construct ���ɱ����ģ��ķ���
TEST(AllocatorTest, ConstructWithArgs) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    alloc.construct(ptr, 42);
    EXPECT_EQ(ptr->value, 42);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// ���� destroy ��������ķ���
TEST(AllocatorTest, DestroySingle) {
    mystl::allocator<TestClass> alloc;
    TestClass* ptr = alloc.allocate();
    alloc.construct(ptr);
    alloc.destroy(ptr);
    alloc.deallocate(ptr);
}

// ���� destroy �������ķ���
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