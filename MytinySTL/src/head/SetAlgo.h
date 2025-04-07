#pragma once
#ifndef SETALGO_H_
#define SETALGO_H_

#include "Iterator.h"
#include "AlgoBase.h"

namespace mystl
{
    // set_union
    // 计算两个集合的并集，结果存储在 result 中
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_union(InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (*first1 < *first2)
            {
                *result = *first1;
                ++first1;
            }
            else if (*first2 < *first1)
            {
                *result = *first2;
                ++first2;
            }
            else
            {
                *result = *first1;
                ++first1;
                ++first2;
            }
            ++result;
        }
        // 将剩余元素拷贝到 result
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_union(InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result, Compared comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(*first1, *first2))
            {
                *result = *first1;
                ++first1;
            }
            else if (comp(*first2, *first1))
            {
                *result = *first2;
                ++first2;
            }
            else
            {
                *result = *first1;
                ++first1;
                ++first2;
            }
            ++result;
        }
        // 将剩余元素拷贝到 result
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    // set_intersection
    // 计算两个集合的交集，结果存储在 result 中
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (*first1 < *first2)
            {
                ++first1;
            }
            else if (*first2 < *first1)
            {
                ++first2;
            }
            else
            {
                *result = *first1;
                ++first1;
                ++first2;
                ++result;
            }
        }
        return result;
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_intersection(InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result, Compared comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(*first1, *first2))
            {
                ++first1;
            }
            else if (comp(*first2, *first1))
            {
                ++first2;
            }
            else
            {
                *result = *first1;
                ++first1;
                ++first2;
                ++result;
            }
        }
        return result;
    }

    // set_difference
    // 计算两个集合的差集，也就是存在于第一个区间但不存在于第二个区间的元素，结果存储在 result 中
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_difference(InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (*first1 < *first2)
            {
                *result = *first1;
                ++first1;
                ++result;
            }
            else if (*first2 < *first1)
            {
                ++first2;
            }
            else
            {
                ++first1;
                ++first2;
            }
        }
        return mystl::copy(first1, last1, result);
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_difference(InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result, Compared comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(*first1, *first2))
            {
                *result = *first1;
                ++first1;
                ++result;
            }
            else if (comp(*first2, *first1))
            {
                ++first2;
            }
            else
            {
                ++first1;
                ++first2;
            }
        }
        return mystl::copy(first1, last1, result);
    }

    // set_symmetric_difference
    // 计算两个集合的对称差集，结果存储在 result 中
    template <class InputIter1, class InputIter2, class OutputIter>
    OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (*first1 < *first2)
            {
                *result = *first1;
                ++first1;
                ++result;
            }
            else if (*first2 < *first1)
            {
                *result = *first2;
                ++first2;
                ++result;
            }
            else
            {
                ++first1;
                ++first2;
            }
        }
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }

    // 重载版本使用函数对象 comp 代替比较操作
    template <class InputIter1, class InputIter2, class OutputIter, class Compared>
    OutputIter set_symmetric_difference(InputIter1 first1, InputIter1 last1,
        InputIter2 first2, InputIter2 last2,
        OutputIter result, Compared comp)
    {
        while (first1 != last1 && first2 != last2)
        {
            if (comp(*first1, *first2))
            {
                *result = *first1;
                ++first1;
                ++result;
            }
            else if (comp(*first2, *first1))
            {
                *result = *first2;
                ++first2;
                ++result;
            }
            else
            {
                ++first1;
                ++first2;
            }
        }
        return mystl::copy(first2, last2, mystl::copy(first1, last1, result));
    }
}
#endif // SETALGO_H_