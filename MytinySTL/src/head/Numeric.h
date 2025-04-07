#pragma once
#ifndef MYTINYSTL_NUMERIC_H_
#define MYTINYSTL_NUMERIC_H_

// ���ͷ�ļ������� mystl ����ֵ�㷨

#include "Iterator.h"

namespace mystl
{
    // accumulate
    template <class InputIter, class T>
    T accumulate(InputIter first, InputIter last, T init)
    {
        for (; first != last; ++first)
        {
            init += *first;
        }
        return init;
    }

	// BinaryOp������
    template <class InputIter, class T, class BinaryOp>
    T accumulate(InputIter first, InputIter last, T init, BinaryOp binary_op)
    {
        for (; first != last; ++first)
        {
            init = binary_op(init, *first);
        }
        return init;
    }

    //adjacent_difference
    // ��������Ԫ�صĲ�ֵ��������浽�� result Ϊ��ʼ��������
    template <class InputIter, class OutputIter>
    OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result)
    {
        if (first == last)  return result;
        *result = *first;  // ��¼��һ��Ԫ��
        auto value = *first;
        while (++first != last)
        {
            auto tmp = *first;
            *++result = tmp - value;
            value = tmp;
        }
        return ++result;
    }

    // BinaryOp������
    template <class InputIter, class OutputIter, class BinaryOp>
    OutputIter adjacent_difference(InputIter first, InputIter last, OutputIter result,
        BinaryOp binary_op)
    {
        if (first == last)  return result;
        *result = *first;  // ��¼��һ��Ԫ��
        auto value = *first;
        while (++first != last)
        {
            auto tmp = *first;
            *++result = binary_op(tmp, value);
            value = tmp;
        }
        return ++result;
    }

    // �� init Ϊ��ֵ����������������ڻ�  
    template <class InputIter1, class InputIter2, class T>
    T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            init = init + (*first1 * *first2);
        }
        return init;
    }

    // �Զ��� operator+ �� operator*
    template <class InputIter1, class InputIter2, class T, class BinaryOp1, class BinaryOp2>
    T inner_product(InputIter1 first1, InputIter1 last1, InputIter2 first2, T init,
        BinaryOp1 binary_op1, BinaryOp2 binary_op2)
    {
        for (; first1 != last1; ++first1, ++first2)
        {
            init = binary_op1(init, binary_op2(*first1, *first2));
        }
        return init;
    }



    // ���[first, last)���� value Ϊ��ֵ��ʼ����
    template <class ForwardIter, class T>
    void iota(ForwardIter first, ForwardIter last, T value)
    {
        while (first != last)
        {
            *first++ = value;
            ++value;
        }
    }

    //����ֲ��ۼ���ͣ�������浽�� result Ϊ��ʼ��������
    template <class InputIter, class OutputIter>
    OutputIter partial_sum(InputIter first, InputIter last, OutputIter result)
    {
        if (first == last)  return result;
        *result = *first;  // ��¼��һ��Ԫ��
        auto value = *first;
        while (++first != last)
        {
            value = value + *first;
            *++result = value;
        }
        return ++result;
    }

    // ���оֲ������Զ����Ԫ����
    template <class InputIter, class OutputIter, class BinaryOp>
    OutputIter partial_sum(InputIter first, InputIter last, OutputIter result,
        BinaryOp binary_op)
    {
        if (first == last)  return result;
        *result = *first;  //��¼��һ��Ԫ��
        auto value = *first;
        while (++first != last)
        {
            value = binary_op(value, *first);
            *++result = value;
        }
        return ++result;
    }

} // namespace mystl
#endif // !MYTINYSTL_NUMERIC_H_

