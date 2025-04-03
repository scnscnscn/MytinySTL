#include "pch.h"
#include "C:\Users\WLQVi\Desktop\CPPProject\MytinySTL\MytinySTL\src\head\Iterator.h" 
using namespace std;

// ���Ե����������ж���ع���
TEST(IteratorTest, IteratorTypeCheck) {
    int* intPtr = nullptr;
    const int* constIntPtr = nullptr;

    // ����ԭ��ָ����������ʵ�����
    EXPECT_TRUE(mystl::is_random_access_iterator<int*>::value);
    EXPECT_TRUE(mystl::is_random_access_iterator<const int*>::value);

    // ��������������жϣ������Զ���һ��������������ࣩ
    struct SimpleInputIterator : public mystl::iterator<mystl::input_iterator_tag, int> {
        SimpleInputIterator(int* ptr) : current(ptr) {}
        int* current;
        bool operator!=(const SimpleInputIterator& other) const { return current != other.current; }
        SimpleInputIterator& operator++() { ++current; return *this; }
        int* base() const { return current; } // ��� base ��Ա����
    };

    // ��������������жϣ������Զ���һ��������������ࣩ
    struct SimpleOutputIterator : public mystl::iterator<mystl::output_iterator_tag, int> {};

    // ����ǰ��������жϣ������Զ���һ����ǰ��������ࣩ
    struct SimpleForwardIterator : public mystl::iterator<mystl::forward_iterator_tag, int> {};

    // ����˫��������жϣ������Զ���һ����˫��������ࣩ
    struct SimpleBidirectionalIterator : public mystl::iterator<mystl::bidirectional_iterator_tag, int> {
        SimpleBidirectionalIterator(int* ptr) : current(ptr) {}
        int* current;
        SimpleBidirectionalIterator& operator++() { ++current; return *this; }
        SimpleBidirectionalIterator& operator--() { --current; return *this; }
        bool operator!=(const SimpleBidirectionalIterator& other) const { return current != other.current; }
        int* base() const { return current; } // ��� base ��Ա����
    };

    // ���Ե�������Ч���ж�
    EXPECT_TRUE(mystl::is_iterator<SimpleInputIterator>::value);
    EXPECT_TRUE(mystl::is_iterator<SimpleOutputIterator>::value);
    EXPECT_TRUE(mystl::is_iterator<SimpleForwardIterator>::value);
    EXPECT_TRUE(mystl::is_iterator<SimpleBidirectionalIterator>::value);
    EXPECT_TRUE(mystl::is_iterator<int*>::value);
}

// ���Ե������������
TEST(IteratorTest, DistanceCalculation) {
    int arr[] = { 1, 2, 3, 4, 5 };
    int* first = arr;
    int* last = arr + 5;

    // ����������ʵ������ľ������
    mystl::iterator_traits<int*>::difference_type dist = mystl::distance(first, last);
    EXPECT_EQ(dist, 5);

    // �����Զ���һ������������������ڲ�������������������
    struct SimpleInputIterator : public mystl::iterator<mystl::input_iterator_tag, int> {
        SimpleInputIterator(int* ptr) : current(ptr) {}
        int* current;
        bool operator!=(const SimpleInputIterator& other) const { return current != other.current; }
        SimpleInputIterator& operator++() { ++current; return *this; }
        int* base() const { return current; } // ��� base ��Ա����
    };

    SimpleInputIterator inputFirst(arr);
    SimpleInputIterator inputLast(arr + 5);
    mystl::iterator_traits<SimpleInputIterator>::difference_type inputDist = mystl::distance(inputFirst, inputLast);
    EXPECT_EQ(inputDist, 5);
}

// ���Ե�����ǰ������
TEST(IteratorTest, AdvanceOperation) {
    int arr[] = { 1, 2, 3, 4, 5 };
    int* ptr = arr;

    // ����������ʵ�������ǰ������
    mystl::advance(ptr, 3);
    EXPECT_EQ(*ptr, 4);

    // �����Զ���һ����˫������������ڲ���˫�������ǰ������
    struct SimpleBidirectionalIterator : public mystl::iterator<mystl::bidirectional_iterator_tag, int> {
        SimpleBidirectionalIterator(int* ptr) : current(ptr) {}
        int* current;
        SimpleBidirectionalIterator& operator++() { ++current; return *this; }
        SimpleBidirectionalIterator& operator--() { --current; return *this; }
        bool operator!=(const SimpleBidirectionalIterator& other) const { return current != other.current; }
        int* base() const { return current; } // ��� base ��Ա����
    };

    SimpleBidirectionalIterator bidirectionalIter(arr);
    mystl::advance(bidirectionalIter, 2);
    EXPECT_EQ(*(bidirectionalIter.base()), 3);
    mystl::advance(bidirectionalIter, -1);
    EXPECT_EQ(*(bidirectionalIter.base()), 2);

    // �����Զ���һ������������������ڲ������������ǰ������
    struct SimpleInputIterator : public mystl::iterator<mystl::input_iterator_tag, int> {
        SimpleInputIterator(int* ptr) : current(ptr) {}
        int* current;
        SimpleInputIterator& operator++() { ++current; return *this; }
        bool operator!=(const SimpleInputIterator& other) const { return current != other.current; }
        int* base() const { return current; } // ��� base ��Ա����
    };

    SimpleInputIterator inputIter(arr);
    mystl::advance(inputIter, 3);
    EXPECT_EQ(*(inputIter.base()), 4);
}

// ���Է����������ز���
TEST(IteratorTest, ReverseIteratorOperations) {
    int arr[] = { 1, 2, 3, 4, 5 };
    int* first = arr;
    int* last = arr + 5;

    mystl::reverse_iterator<int*> rfirst(last);
    mystl::reverse_iterator<int*> rlast(first);

    // ���Է�������������ò���
    EXPECT_EQ(*rfirst, 5);

    // ���Է��������ǰ�õ�������
    ++rfirst;
    EXPECT_EQ(*rfirst, 4);

    // ���Է�����������õ�������
    mystl::reverse_iterator<int*> rfirstCopy = rfirst;
    rfirstCopy++;
    EXPECT_EQ(*rfirstCopy, 3);

    // ���Է��������ǰ�õݼ�����
    --rlast;
    EXPECT_EQ(*rlast, 1); 

    // ���Է�����������õݼ�����
    mystl::reverse_iterator<int*> rlastCopy = rlast;
    rlastCopy--;
    EXPECT_EQ(*rlastCopy, 2); 

    // ���Է���������ӷ�����
    mystl::reverse_iterator<int*> rnew = rfirst + 2;
    EXPECT_EQ(*rnew, 2);

    // ���Է����������������
    mystl::reverse_iterator<int*> rsub = rlast - 1;
    EXPECT_EQ(*rsub, 2); 

    // ���Է�����������ϸ�ֵ������ +=
    rfirst += 1;
    EXPECT_EQ(*rfirst, 3);

    // ���Է�����������ϸ�ֵ������ -=
    rlast -= 1;
    EXPECT_EQ(*rlast, 2); 

    // ���Է���������±������
    EXPECT_EQ(rfirst[2], 1);

    // ���Է��������֮��ľ������
    mystl::reverse_iterator<int*>::difference_type rdist = rlast - rfirst;
    EXPECT_EQ(rdist, 1);

    // ���Է���������Ƚϲ�����
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