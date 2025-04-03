#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Util.h"

class MyClass {
public:
    MyClass() : data(new int(0)), movedFrom(false) {
        std::cout << "Default constructor" << std::endl;
    }

    MyClass(const MyClass& other) : data(new int(*other.data)), movedFrom(false) {
        std::cout << "Copy constructor" << std::endl;
    }

    MyClass(MyClass&& other) noexcept : data(other.data), movedFrom(false) {
        other.data = nullptr;
        other.movedFrom = true;
        std::cout << "Move constructor" << std::endl;
    }

    ~MyClass() {
        delete data;
    }

    bool isMovedFrom() const {
        return movedFrom;
    }

private:
    int* data;
    bool movedFrom;
};

// 测试 move
TEST(UtilTest, TestMove) {
    MyClass obj1;
    MyClass obj2 = mystl::move(obj1);
    EXPECT_TRUE(obj1.isMovedFrom());
}

// 辅助函数，用于测试 forward
template<typename T>
void forwardHelper(T&& arg) {
    MyClass obj = mystl::forward<T>(arg);
    if constexpr (std::is_lvalue_reference_v<T>) {
        EXPECT_FALSE(arg.isMovedFrom());
    }
    else {
        EXPECT_TRUE(arg.isMovedFrom());
    }
}

// 测试 forward 转发左值
TEST(UtilTest, TestForwardLvalue) {
    MyClass obj;
    forwardHelper(obj);
}

// 测试 forward 转发右值
TEST(UtilTest, TestForwardRvalue) {
    forwardHelper(MyClass());
}

TEST(UtilTest, TestSwap) {
	int a = 1;
	int b = 2;
    mystl::swap(a, b);
    EXPECT_EQ(a, 2);
    EXPECT_EQ(b, 1);

	int& c = a;
	int& d = b;
	mystl::swap(c, d);
	EXPECT_EQ(c, 1);
	EXPECT_EQ(d, 2);
}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "UtilTest.*";
//    return RUN_ALL_TESTS();
//}

 