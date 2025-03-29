#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Construct.h"

class TestClass {
public:
    TestClass() : value(0) { std::cout << "TestClass default constructor" << std::endl; }
    TestClass(int v) : value(v) { std::cout << "TestClass parameterized constructor" << std::endl; }
    ~TestClass() { std::cout << "TestClass destructor" << std::endl; }
    int value;
};

// ����Ĭ�Ϲ��캯��
TEST(ConstructTest, ConstructDefault) {
    alignas(TestClass) char buffer[sizeof(TestClass)];
    TestClass* ptr = reinterpret_cast<TestClass*>(buffer);
    mystl::construct(ptr);
    EXPECT_EQ(ptr->value, 0);
    mystl::destroy(ptr);
}

// ���Դ������Ĺ��캯��
TEST(ConstructTest, ConstructWithParameter) {
    alignas(TestClass) char buffer[sizeof(TestClass)];
    TestClass* ptr = reinterpret_cast<TestClass*>(buffer);
    mystl::construct(ptr, 42);
    EXPECT_EQ(ptr->value, 42);
    mystl::destroy(ptr);
}

// �������ٵ�������Χ
TEST(ConstructTest, DestroyRange) {
    alignas(TestClass) char buffer[3 * sizeof(TestClass)];
    TestClass* array = reinterpret_cast<TestClass*>(buffer);
    for (int i = 0; i < 3; ++i) {
        mystl::construct(array + i, i);
    }
    mystl::destroy(array, array + 3);
}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "ConstructTest.*";
//    return RUN_ALL_TESTS();
//}


