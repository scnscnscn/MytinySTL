#pragma once
#ifndef HEAP_ALGO_H
#define HEAP_ALGO_H
#include "Iterator.h"
// 最大堆的定义是：对于每一个节点i，i的值大于等于它的子节点的值
// 最小堆的定义是：对于每一个节点i，i的值小于等于它的子节点的值
// 也就是说不报错，但结果几乎一定错
namespace mystl
{   // heap分最大堆和最小堆，默认是最大堆
	// push_heap
    template <class RandomIter, class Distance, class T>
    void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value)
    {
        auto parent = (holeIndex - 1) / 2;
		while (holeIndex > topIndex && *(first + parent) < value)//当 holeIndex > topIndex 时，说明当前节点在树的上半部分
		{                                                       // 先将父节点与当前节点进行比较，若父节点小于当前节点，则将父节点下移
			                                                    // 否则就将当前节点放入合适的位置
            // max-heap使用 <
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;
    }

    template <class RandomIter, class Distance>
    void push_heap_d(RandomIter first, RandomIter last, Distance*)//该函数的作用是将新元素插入到堆中
    {                                                             // 先将新元素放在容器的尾部，然后调整为 max-heap
        mystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0), *(last - 1));
    }

    template <class RandomIter>

	void push_heap(RandomIter first, RandomIter last)
	{
		mystl::push_heap_d(first, last, distance_type(first));
	}

    // 重载版本使用函数对象 comp 代替比较操作
    template <class RandomIter, class Distance, class T, class Compared>
    void push_heap_aux(RandomIter first, Distance holeIndex, Distance topIndex, T value,
        Compared comp)
    {
        auto parent = (holeIndex - 1) / 2;
        while (holeIndex > topIndex && comp(*(first + parent), value))
        {
            *(first + holeIndex) = *(first + parent);
            holeIndex = parent;
            parent = (holeIndex - 1) / 2;
        }
        *(first + holeIndex) = value;
    }

    template <class RandomIter, class Compared, class Distance>
    void push_heap_d(RandomIter first, RandomIter last, Distance*, Compared comp)
    {
        mystl::push_heap_aux(first, (last - first) - 1, static_cast<Distance>(0),
            *(last - 1), comp);
    }

    template <class RandomIter, class Compared>
    void push_heap(RandomIter first, RandomIter last, Compared comp)
    {
        mystl::push_heap_d(first, last, distance_type(first), comp);
    }

    // pop_heap
    template <class RandomIter, class T, class Distance>
    void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value)
    {
        // 先进行下溯(percolate down)过程
        auto topIndex = holeIndex;
        auto rchild = 2 * holeIndex + 2;
        while (rchild < len)
        {
            if (*(first + rchild) < *(first + rchild - 1))
                --rchild;
            *(first + holeIndex) = *(first + rchild);
            holeIndex = rchild;
            rchild = 2 * (rchild + 1);
        }
        if (rchild == len)
        {  // 如果没有右子节点
            *(first + holeIndex) = *(first + (rchild - 1));
            holeIndex = rchild - 1;
        }
        // 再执行一次上溯(percolate up)过程
        mystl::push_heap_aux(first, holeIndex, topIndex, value);
    }

    template <class RandomIter, class T, class Distance>
    void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result, T value,
        Distance*)
    {
        // 先将首值调至尾节点，然后调整[first, last - 1)使之重新成为一个 max-heap
        *result = *first;
        mystl::adjust_heap(first, static_cast<Distance>(0), last - first, value);
    }

    template <class RandomIter>
    void pop_heap(RandomIter first, RandomIter last)
    {
        mystl::pop_heap_aux(first, last - 1, last - 1, *(last - 1), distance_type(first));
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class RandomIter, class T, class Distance, class Compared>
    void adjust_heap(RandomIter first, Distance holeIndex, Distance len, T value,
        Compared comp)
    {
        // 先进行下溯(percolate down)过程
        auto topIndex = holeIndex;
        auto rchild = 2 * holeIndex + 2;
        while (rchild < len)
        {
            if (comp(*(first + rchild), *(first + rchild - 1)))  --rchild;
            *(first + holeIndex) = *(first + rchild);
            holeIndex = rchild;
            rchild = 2 * (rchild + 1);
        }
        if (rchild == len)
        {
            *(first + holeIndex) = *(first + (rchild - 1));
            holeIndex = rchild - 1;
        }
        // 再执行一次上溯(percolate up)过程
        mystl::push_heap_aux(first, holeIndex, topIndex, value, comp);
    }

    template <class RandomIter, class T, class Distance, class Compared>
    void pop_heap_aux(RandomIter first, RandomIter last, RandomIter result,
        T value, Distance*, Compared comp)
    {
        *result = *first;  // 先将尾指设置成首值，即尾指为欲求结果
        mystl::adjust_heap(first, static_cast<Distance>(0), last - first, value, comp);
    }

    template <class RandomIter, class Compared>
    void pop_heap(RandomIter first, RandomIter last, Compared comp)
    {
        mystl::pop_heap_aux(first, last - 1, last - 1, *(last - 1),
            distance_type(first), comp);
    }

    // sort_heap
    template <class RandomIter>
    void sort_heap(RandomIter first, RandomIter last)
    {
        // 每执行一次 pop_heap，最大的元素都被放到尾部，直到容器最多只有一个元素，完成排序
        while (last - first > 1)
        {
            mystl::pop_heap(first, last--);
        }
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class RandomIter, class Compared>
    void sort_heap(RandomIter first, RandomIter last, Compared comp)
    {
        while (last - first > 1)
        {
            mystl::pop_heap(first, last--, comp);
        }
    }

    // make_heap
    template <class RandomIter, class Distance>
    void make_heap_aux(RandomIter first, RandomIter last, Distance*)
    {
        if (last - first < 2)
            return;
        auto len = last - first;
        auto holeIndex = (len - 2) / 2;
        while (true)
        {
            // 重排以 holeIndex 为首的子树
            mystl::adjust_heap(first, holeIndex, len, *(first + holeIndex));
            if (holeIndex == 0)
                return;
            holeIndex--;
        }
    }

    template <class RandomIter>
    void make_heap(RandomIter first, RandomIter last)
    {
        mystl::make_heap_aux(first, last, distance_type(first));;
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class RandomIter, class Distance, class Compared>
    void make_heap_aux(RandomIter first, RandomIter last, Distance*, Compared comp)
    {
        if (last - first < 2)
            return;
        auto len = last - first;
        auto holeIndex = (len - 2) / 2;
        while (true)
        {
            // 重排以 holeIndex 为首的子树
            mystl::adjust_heap(first, holeIndex, len, *(first + holeIndex), comp);
            if (holeIndex == 0)
                return;
            holeIndex--;
        }
    }

    template <class RandomIter, class Compared>
    void make_heap(RandomIter first, RandomIter last, Compared comp)
    {
        mystl::make_heap_aux(first, last, distance_type(first), comp);
    }
}
#endif // !HEAP_ALGO_H
