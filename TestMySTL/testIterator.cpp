#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Iterator.h" 
using namespace std;

// 测试迭代器类型判断相关功能
TEST(IteratorTest, IteratorTypeCheck) {
    int* intPtr = nullptr;
    const int* constIntPtr = nullptr;

    // 测试原生指针是随机访问迭代器
    EXPECT_TRUE(mystl::is_random_access_iterator<int*>::value);
    EXPECT_TRUE(mystl::is_random_access_iterator<const int*>::value);

    // 测试输入迭代器判断（假设自定义一个简单输入迭代器类）
    struct SimpleInputIterator : public mystl::iterator<mystl::input_iterator_tag, int> {
        SimpleInputIterator(int* ptr) : current(ptr) {}
        int* current;
        bool operator!=(const SimpleInputIterator& other) const { return current != other.current; }
        SimpleInputIterator& operator++() { ++current; return *this; }
        int* base() const { return current; } // 添加 base 成员函数
    };

    // 测试输出迭代器判断（假设自定义一个简单输出迭代器类）
    struct SimpleOutputIterator : public mystl::iterator<mystl::output_iterator_tag, int> {};

    // 测试前向迭代器判断（假设自定义一个简单前向迭代器类）
    struct SimpleForwardIterator : public mystl::iterator<mystl::forward_iterator_tag, int> {};

    // 测试双向迭代器判断（假设自定义一个简单双向迭代器类）
    struct SimpleBidirectionalIterator : public mystl::iterator<mystl::bidirectional_iterator_tag, int> {
        SimpleBidirectionalIterator(int* ptr) : current(ptr) {}
        int* current;
        SimpleBidirectionalIterator& operator++() { ++current; return *this; }
        SimpleBidirectionalIterator& operator--() { --current; return *this; }
        bool operator!=(const SimpleBidirectionalIterator& other) const { return current != other.current; }
        int* base() const { return current; } // 添加 base 成员函数
    };

    // 测试迭代器有效性判断
    EXPECT_TRUE(mystl::is_iterator<SimpleInputIterator>::value);
    EXPECT_TRUE(mystl::is_iterator<SimpleOutputIterator>::value);
    EXPECT_TRUE(mystl::is_iterator<SimpleForwardIterator>::value);
    EXPECT_TRUE(mystl::is_iterator<SimpleBidirectionalIterator>::value);
    EXPECT_TRUE(mystl::is_iterator<int*>::value);
}

// 测试迭代器距离计算
TEST(IteratorTest, DistanceCalculation) {
    int arr[] = { 1, 2, 3, 4, 5 };
    int* first = arr;
    int* last = arr + 5;

    // 测试随机访问迭代器的距离计算
    mystl::iterator_traits<int*>::difference_type dist = mystl::distance(first, last);
    EXPECT_EQ(dist, 5);

    // 假设自定义一个简单输入迭代器类用于测试输入迭代器距离计算
    struct SimpleInputIterator : public mystl::iterator<mystl::input_iterator_tag, int> {
        SimpleInputIterator(int* ptr) : current(ptr) {}
        int* current;
        bool operator!=(const SimpleInputIterator& other) const { return current != other.current; }
        SimpleInputIterator& operator++() { ++current; return *this; }
        int* base() const { return current; } // 添加 base 成员函数
    };

    SimpleInputIterator inputFirst(arr);
    SimpleInputIterator inputLast(arr + 5);
    mystl::iterator_traits<SimpleInputIterator>::difference_type inputDist = mystl::distance(inputFirst, inputLast);
    EXPECT_EQ(inputDist, 5);
}

// 测试迭代器前进操作
TEST(IteratorTest, AdvanceOperation) {
    int arr[] = { 1, 2, 3, 4, 5 };
    int* ptr = arr;

    // 测试随机访问迭代器的前进操作
    mystl::advance(ptr, 3);
    EXPECT_EQ(*ptr, 4);

    // 假设自定义一个简单双向迭代器类用于测试双向迭代器前进操作
    struct SimpleBidirectionalIterator : public mystl::iterator<mystl::bidirectional_iterator_tag, int> {
        SimpleBidirectionalIterator(int* ptr) : current(ptr) {}
        int* current;
        SimpleBidirectionalIterator& operator++() { ++current; return *this; }
        SimpleBidirectionalIterator& operator--() { --current; return *this; }
        bool operator!=(const SimpleBidirectionalIterator& other) const { return current != other.current; }
        int* base() const { return current; } // 添加 base 成员函数
    };

    SimpleBidirectionalIterator bidirectionalIter(arr);
    mystl::advance(bidirectionalIter, 2);
    EXPECT_EQ(*(bidirectionalIter.base()), 3);
    mystl::advance(bidirectionalIter, -1);
    EXPECT_EQ(*(bidirectionalIter.base()), 2);

    // 假设自定义一个简单输入迭代器类用于测试输入迭代器前进操作
    struct SimpleInputIterator : public mystl::iterator<mystl::input_iterator_tag, int> {
        SimpleInputIterator(int* ptr) : current(ptr) {}
        int* current;
        SimpleInputIterator& operator++() { ++current; return *this; }
        bool operator!=(const SimpleInputIterator& other) const { return current != other.current; }
        int* base() const { return current; } // 添加 base 成员函数
    };

    SimpleInputIterator inputIter(arr);
    mystl::advance(inputIter, 3);
    EXPECT_EQ(*(inputIter.base()), 4);
}

// 测试反向迭代器相关操作
TEST(IteratorTest, ReverseIteratorOperations) {
    int arr[] = { 1, 2, 3, 4, 5 };
    int* first = arr;
    int* last = arr + 5;

    mystl::reverse_iterator<int*> rfirst(last);
    mystl::reverse_iterator<int*> rlast(first);

    // 测试反向迭代器解引用操作
    EXPECT_EQ(*rfirst, 5);

    // 测试反向迭代器前置递增操作
    ++rfirst;
    EXPECT_EQ(*rfirst, 4);

    // 测试反向迭代器后置递增操作
    mystl::reverse_iterator<int*> rfirstCopy = rfirst;
    rfirstCopy++;
    EXPECT_EQ(*rfirstCopy, 3);

    // 测试反向迭代器前置递减操作
    --rlast;
    EXPECT_EQ(*rlast, 1); 

    // 测试反向迭代器后置递减操作
    mystl::reverse_iterator<int*> rlastCopy = rlast;
    rlastCopy--;
    EXPECT_EQ(*rlastCopy, 2); 

    // 测试反向迭代器加法操作
    mystl::reverse_iterator<int*> rnew = rfirst + 2;
    EXPECT_EQ(*rnew, 2);

    // 测试反向迭代器减法操作
    mystl::reverse_iterator<int*> rsub = rlast - 1;
    EXPECT_EQ(*rsub, 2); 

    // 测试反向迭代器复合赋值操作符 +=
    rfirst += 1;
    EXPECT_EQ(*rfirst, 3);

    // 测试反向迭代器复合赋值操作符 -=
    rlast -= 1;
    EXPECT_EQ(*rlast, 2); 

    // 测试反向迭代器下标操作符
    EXPECT_EQ(rfirst[2], 1);

    // 测试反向迭代器之间的距离计算
    mystl::reverse_iterator<int*>::difference_type rdist = rlast - rfirst;
    EXPECT_EQ(rdist, 1);

    // 测试反向迭代器比较操作符
    EXPECT_TRUE(rfirst != rlast);
    EXPECT_TRUE(rfirst < rlast);
    EXPECT_TRUE(rlast > rfirst);
    EXPECT_TRUE(rfirst <= rlast);
    EXPECT_TRUE(rlast >= rfirst);
}

//int main(int argc, char** argv) {
//    ::testing::InitGoogleTest(&argc, argv);
//    ::testing::GTEST_FLAG(filter) = "IteratorTest.*";
//    return RUN_ALL_TESTS();
//}