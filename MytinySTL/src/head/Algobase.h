#pragma once
#ifndef ALGOBASE_H_
#define ALGOBASE_H_

#include <cstring>
#include "Iterator.h"
#include "Util.h"
namespace mystl {

//移除可能存在的max和min宏定义
#ifdef max
#pragma message("#undefing marco max")
#undef max
#endif // max

#ifdef min
#pragma message("#undefing marco min")
#undef min
#endif // min

//max
	template <class T>
	const T& max(const T& lhs, const T& rhs) {
		return lhs < rhs ? rhs : lhs;
	}
	//重载版本使用函数对象comp比较器代替<
	template <class T, class Compare>
	const T& max(const T& lhs, const T& rhs, Compare comp) {
		return comp(lhs, rhs) ? rhs : lhs;
	}

	//min
	template <class T>
	const T& min(const T& lhs, const T& rhs) {
		return rhs < lhs ? rhs : lhs;
	}
	//重载版本使用函数对象comp比较器代替<
	template <class T, class Compare>
	const T& min(const T& lhs, const T& rhs, Compare comp) {
		return comp(rhs, lhs) ? rhs : lhs;
	}

	// equal
	template <class InputIter1, class InputIter2>
	bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (*first1 != *first2)
				return false;
		}
		return true;
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class Compared>
	bool equal(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compared comp)
	{
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!comp(*first1, *first2))
				return false;
		}
		return true;
	}
	//iter_swap
	template <class FIter1, class FIter2>
	void iter_swap(FIter1 lhs, FIter2 rhs) {
		mystl::swap(*lhs, *rhs);
	}

	//copy
	template <class InputIter, class OutputIter>
	OutputIter unchecked_copy_cat(InputIter first, InputIter last, OutputIter result,
		mystl::input_iterator_tag)//顺序迭代器
	{
		for (; first != last; ++first, ++result)//只能向前一个一个迭代
		{
			*result = *first;
		}
		return result;
	}

	 
	template <class RandomIter, class OutputIter>
	OutputIter unchecked_copy_cat(RandomIter first, RandomIter last, OutputIter result,
			mystl::random_access_iterator_tag)//随机迭代器
	{
		for (auto n = last - first; n > 0; --n, ++first, ++result)//提前计算n，可以避免多次迭代器的比较
		{
			*result = *first;
		}

		return result;
	}

	//高级封装，使用萃取确定迭代器类型
	template <class InputIter, class OutputIter>
	OutputIter unchecked_copy(InputIter first, InputIter last, OutputIter result)
	{
		return unchecked_copy_cat(first, last, result, iterator_category(first));
	}

	// 为 trivially_copy_assignable 类型提供特化版本
	template <class Tp, class Up>
	typename std::enable_if<
		std::is_same<typename std::remove_const<Tp>::type, Up>::value&&//去除 Tp 类型的常量修饰符后的类型与 Up 类型是否相同
		std::is_trivially_copy_assignable<Up>::value, Up*>::type//Up 类型是否是平凡复制赋值的
		unchecked_copy(Tp* first, Tp* last, Up* result)
	{
		const auto n = static_cast<size_t>(last - first);
		if (n != 0)
			std::memmove(result, first, n * sizeof(Up));
		return result + n;
	}

	template <class InputIter, class OutputIter>
	OutputIter copy(InputIter first, InputIter last, OutputIter result)
	{
		return unchecked_copy(first, last, result);
	}

	//copy_backward,一般适用于两个区间有重叠的情况，避免覆盖
	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		unchecked_copy_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
			BidirectionalIter2 result, mystl::bidirectional_iterator_tag)//双向迭代器
	{
		while (first != last)
			*--result = *--last;
		return result;
	}

	template <class RandomIter1, class BidirectionalIter2>
	BidirectionalIter2
		unchecked_copy_backward_cat(RandomIter1 first, RandomIter1 last,
			BidirectionalIter2 result, mystl::random_access_iterator_tag)//随机迭代器
	{
		for (auto n = last - first; n > 0; --n)
			*--result = *--last;
		return result;
	}

	//高级封装，使用萃取确定迭代器类型
	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		unchecked_copy_backward(BidirectionalIter1 first, BidirectionalIter1 last,
			BidirectionalIter2 result)
	{
		return unchecked_copy_backward_cat(first, last, result,
			iterator_category(first));
	}

	// 为 trivially_copy_assignable 类型提供特化版本
	template <class Tp, class Up>
	typename std::enable_if<
		std::is_same<typename std::remove_const<Tp>::type, Up>::value&&//去除 Tp 类型的常量修饰符后的类型与 Up 类型是否相同
		std::is_trivially_copy_assignable<Up>::value,//Up 类型是否是平凡复制赋值的
		Up*>::type
		unchecked_copy_backward(Tp* first, Tp* last, Up* result)
	{
		const auto n = static_cast<size_t>(last - first);
		if (n != 0)
		{
			result -= n;
			std::memmove(result, first, n * sizeof(Up));
		}
		return result;
	}

	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		copy_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
	{
		return unchecked_copy_backward(first, last, result);
	}

	// copy_if
	template <class InputIter, class OutputIter, class UnaryPredicate>//UnaryPredicate单元判断式
	OutputIter
		copy_if(InputIter first, InputIter last, OutputIter result, UnaryPredicate unary_pred)
	{
		for (; first != last; ++first)
		{
			if (unary_pred(*first))
				*result++ = *first;
		}
		return result;
	}
	// copy_n
	//萃取迭代器类型
	template <class InputIter, class Size, class OutputIter>
	mystl::pair<InputIter, OutputIter>
		unchecked_copy_n(InputIter first, Size n, OutputIter result, mystl::input_iterator_tag)//顺序迭代器
	{
		for (; n > 0; --n, ++first, ++result)
		{
			*result = *first;
		}
		return mystl::pair<InputIter, OutputIter>(first, result);
	}

	template <class RandomIter, class Size, class OutputIter>
	mystl::pair<RandomIter, OutputIter>
		unchecked_copy_n(RandomIter first, Size n, OutputIter result,
			mystl::random_access_iterator_tag)//随机迭代器
	{
		auto last = first + n;
		return mystl::pair<RandomIter, OutputIter>(last, mystl::copy(first, last, result));
	}
	//高级封装
	template <class InputIter, class Size, class OutputIter>
	mystl::pair<InputIter, OutputIter>
		copy_n(InputIter first, Size n, OutputIter result)
	{
		return unchecked_copy_n(first, n, result, iterator_category(first));
	}

	// move
	template <class InputIter, class OutputIter>
	OutputIter
		unchecked_move_cat(InputIter first, InputIter last, OutputIter result,
			mystl::input_iterator_tag)//顺序迭代器
	{
		for (; first != last; ++first, ++result)
		{
			*result = mystl::move(*first);
		}
		return result;
	}

	template <class RandomIter, class OutputIter>
	OutputIter
		unchecked_move_cat(RandomIter first, RandomIter last, OutputIter result,
			mystl::random_access_iterator_tag)//随机迭代器
	{
		for (auto n = last - first; n > 0; --n, ++first, ++result)
		{
			*result = mystl::move(*first);
		}
		return result;
	}

	template <class InputIter, class OutputIter>
	OutputIter
		unchecked_move(InputIter first, InputIter last, OutputIter result)
	{
		return unchecked_move_cat(first, last, result, iterator_category(first));
	}

	// 为 trivially_copy_assignable 类型提供特化版本
	template <class Tp, class Up>
	typename std::enable_if<
		std::is_same<typename std::remove_const<Tp>::type, Up>::value&&
		std::is_trivially_move_assignable<Up>::value,
		Up*>::type
		unchecked_move(Tp* first, Tp* last, Up* result)
	{
		const size_t n = static_cast<size_t>(last - first);
		if (n != 0)
			std::memmove(result, first, n * sizeof(Up));
		return result + n;
	}

	template <class InputIter, class OutputIter>
	OutputIter move(InputIter first, InputIter last, OutputIter result)
	{
		return unchecked_move(first, last, result);
	}
	// move_backward
	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		unchecked_move_backward_cat(BidirectionalIter1 first, BidirectionalIter1 last,
			BidirectionalIter2 result, mystl::bidirectional_iterator_tag)//双向迭代器
	{
		while (first != last)
			*--result = mystl::move(*--last);
		return result;
	}

	template <class RandomIter1, class RandomIter2>
	RandomIter2
		unchecked_move_backward_cat(RandomIter1 first, RandomIter1 last,
			RandomIter2 result, mystl::random_access_iterator_tag)//随机迭代器
	{
		for (auto n = last - first; n > 0; --n)
			*--result = mystl::move(*--last);
		return result;
	}

	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		unchecked_move_backward(BidirectionalIter1 first, BidirectionalIter1 last,
			BidirectionalIter2 result)
	{
		return unchecked_move_backward_cat(first, last, result,
			iterator_category(first));
	}

	// 为 trivially_copy_assignable 类型提供特化版本
	template <class Tp, class Up>
	typename std::enable_if<
		std::is_same<typename std::remove_const<Tp>::type, Up>::value&&
		std::is_trivially_move_assignable<Up>::value,
		Up*>::type
		unchecked_move_backward(Tp* first, Tp* last, Up* result)
	{
		const size_t n = static_cast<size_t>(last - first);
		if (n != 0)
		{
			result -= n;
			std::memmove(result, first, n * sizeof(Up));
		}
		return result;
	}

	template <class BidirectionalIter1, class BidirectionalIter2>
	BidirectionalIter2
		move_backward(BidirectionalIter1 first, BidirectionalIter1 last, BidirectionalIter2 result)
	{
		return unchecked_move_backward(first, last, result);
	}

	// fill_n
	template <class OutputIter, class Size, class T>
	OutputIter unchecked_fill_n(OutputIter first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
		{
			*first = value;
		}
		return first;
	}

	// 为 one-byte 类型提供特化版本
	template <class Tp, class Size, class Up>
	typename std::enable_if<
		std::is_integral<Tp>::value && sizeof(Tp) == 1 &&
		!std::is_same<Tp, bool>::value&&
		std::is_integral<Up>::value && sizeof(Up) == 1,
		Tp*>::type
		unchecked_fill_n(Tp* first, Size n, Up value)
	{
		if (n > 0)
		{
			std::memset(first, (unsigned char)value, (size_t)(n));
		}
		return first + n;
	}

	template <class OutputIter, class Size, class T>
	OutputIter fill_n(OutputIter first, Size n, const T& value)
	{
		return unchecked_fill_n(first, n, value);
	}

	// fill
	template <class ForwardIter, class T>
	void fill_cat(ForwardIter first, ForwardIter last, const T& value,
		mystl::forward_iterator_tag)
	{
		for (; first != last; ++first)
		{
			*first = value;
		}
	}

	template <class RandomIter, class T>
	void fill_cat(RandomIter first, RandomIter last, const T& value,
		mystl::random_access_iterator_tag)
	{
		fill_n(first, last - first, value);
	}

	template <class ForwardIter, class T>
	void fill(ForwardIter first, ForwardIter last, const T& value)
	{
		fill_cat(first, last, value, iterator_category(first));
	}

	// lexicographical_compare 
	// (1)如果第一序列的元素较小，返回 true ，否则返回 false
	// (2)如果到达 last1 而尚未到达 last2 返回 true
	// (3)如果到达 last2 而尚未到达 last1 返回 false
	// (4)如果同时到达 last1 和 last2 返回 false
	template <class InputIter1, class InputIter2>
	bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (*first1 < *first2)
				return true;
			if (*first2 < *first1)
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class Compred>
	bool lexicographical_compare(InputIter1 first1, InputIter1 last1,
		InputIter2 first2, InputIter2 last2, Compred comp)
	{
		for (; first1 != last1 && first2 != last2; ++first1, ++first2)
		{
			if (comp(*first1, *first2))
				return true;
			if (comp(*first2, *first1))
				return false;
		}
		return first1 == last1 && first2 != last2;
	}

	//// 针对 const unsigned char* 的特化版本
	//inline bool lexicographical_compare(const unsigned char* first1,
	//		const unsigned char* last1,
	//		const unsigned char* first2,
	//		const unsigned char* last2) {
	//		const auto len1 = last1 - first1;
	//		const auto len2 = last2 - first2;
	//		const auto result = std::memcmp(first1, first2, std::min(len1, len2));
	//		return result != 0 ? result < 0 : len1 < len2;
	//	}
	// 针对 const unsigned char* 的特化版本

	template <class InputIter1, class InputIter2>
	mystl::pair<InputIter1, InputIter2>
		mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2)
	{
		while (first1 != last1 && *first1 == *first2)
		{
			++first1;
			++first2;
		}
		return mystl::pair<InputIter1, InputIter2>(first1, first2);
	}

	// 重载版本使用函数对象 comp 代替比较操作
	template <class InputIter1, class InputIter2, class Compred>
	mystl::pair<InputIter1, InputIter2>
		mismatch(InputIter1 first1, InputIter1 last1, InputIter2 first2, Compred comp)
	{
		while (first1 != last1 && comp(*first1, *first2))
		{
			++first1;
			++first2;
		}
		return mystl::pair<InputIter1, InputIter2>(first1, first2);
	}
} 
#endif // !ALGOBASE_H_