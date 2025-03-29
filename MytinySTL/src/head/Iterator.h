#ifndef MYTINYSTL_ITERATOR_H_
#define MYTINYSTL_ITERATOR_H_

#include <cstddef>
#include "TypeTraits.h"

namespace mystl
{

    // input_iterator_tag: 输入迭代器，只支持单向、只读操作，每次递增后原迭代器失效。
    struct input_iterator_tag {};
    // output_iterator_tag: 输出迭代器，只支持单向、只写操作，每次递增后原迭代器失效。
    struct output_iterator_tag {};
    // forward_iterator_tag: 前向迭代器，支持单向读写操作，可多次使用。
    struct forward_iterator_tag : public input_iterator_tag {};
    // bidirectional_iterator_tag: 双向迭代器，支持双向读写操作。
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    // random_access_iterator_tag: 随机访问迭代器，支持随机访问，可进行任意偏移操作。
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    // Category: 迭代器类别
    // T: 指向的数据类型
    // Distance: 迭代距离类型，默认为 ptrdiff_t
    // Pointer: 指针类型，默认为 T*
    // Reference: 引用类型，默认为 T&
    // 
    // 两步萃取过程，第一步判断是否有iterator_category
    // 第二步判断iterator_category是否可以转换
    template <class Category, class T, class Distance = ptrdiff_t,
        class Pointer = T*, class Reference = T&>
    struct iterator
    {
        typedef Category                             iterator_category;
        typedef T                                    value_type;
        typedef Pointer                              pointer;
        typedef Reference                            reference;
        typedef Distance                             difference_type;
    };

    // iterator traits
    template <class T>
    struct has_iterator_cat
    {
    private:
        // 编译器通常会选择更特例化的版本
        struct two { char a; char b; };
        // 通用版本，当类型 T 没有 iterator_category 成员时匹配此版本
        template <class U> static two test(...);
        // 特化版本，当类型 T 有 iterator_category 成员时匹配此版本
        template <class U> static char test(typename U::iterator_category* = 0);
    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };

    // 迭代器特性萃取的实现模板
    // 当第二个模板参数为 false 时，不进行萃取
    template <class Iterator, bool>
    struct iterator_traits_impl {};

    // 当第二个模板参数为 true 时，进行迭代器特性萃取
    template <class Iterator>
    struct iterator_traits_impl<Iterator, true>
    {
        // 迭代器类别
        typedef typename Iterator::iterator_category iterator_category;
        // 指向的数据类型
        typedef typename Iterator::value_type        value_type;
        // 指针类型
        typedef typename Iterator::pointer           pointer;
        // 引用类型
        typedef typename Iterator::reference         reference;
        // 迭代距离类型
        typedef typename Iterator::difference_type   difference_type;
    };

    // 迭代器特性萃取的辅助模板
    // 当第二个模板参数为 false 时，不进行萃取
    template <class Iterator, bool>
    struct iterator_traits_helper {};

    // 当第二个模板参数为 true 时，根据迭代器类别是否可转换为 input_iterator_tag 或 output_iterator_tag 进行萃取
    template <class Iterator>
    struct iterator_traits_helper<Iterator, true>
        : public iterator_traits_impl<Iterator,
        std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
        std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
    {
    };

    // 萃取迭代器的特性
    // 通过 has_iterator_cat 检测迭代器是否有 iterator_category 成员，然后调用 iterator_traits_helper 进行萃取
    template <class Iterator>
    struct iterator_traits
        : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {
    };

    // 针对原生指针的偏特化版本
    template <class T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag           iterator_category;
        typedef T                                    value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ptrdiff_t                            difference_type;
    };

    // 针对常量原生指针的偏特化版本
    template <class T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag           iterator_category;
        typedef T                                    value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef ptrdiff_t                            difference_type;
    };

    // 检测迭代器的 iterator_category 是否可转换为指定类型 U
    template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of
        : public m_bool_constant<std::is_convertible<
        typename iterator_traits<T>::iterator_category, U>::value>
    {
    };

    // 当迭代器没有 iterator_category 成员时，返回 false
    template <class T, class U>
    struct has_iterator_cat_of<T, U, false> : public m_false_type {};

    // 检测迭代器是否恰好为输入迭代器（不是前向迭代器）
    template <class Iter>
    struct is_exactly_input_iterator : public m_bool_constant<has_iterator_cat_of<Iter, input_iterator_tag>::value &&
        !has_iterator_cat_of<Iter, forward_iterator_tag>::value> {
    };

    // 检测迭代器是否为输入迭代器
    template <class Iter>
    struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};

    // 检测迭代器是否为输出迭代器
    template <class Iter>
    struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};

    // 检测迭代器是否为前向迭代器
    template <class Iter>
    struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

    // 检测迭代器是否为双向迭代器
    template <class Iter>
    struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

    // 检测迭代器是否为随机访问迭代器
    template <class Iter>
    struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

    // 检测迭代器是否为有效的迭代器（输入或输出迭代器）
    template <class Iterator>
    struct is_iterator :
        public m_bool_constant<is_input_iterator<Iterator>::value ||
        is_output_iterator<Iterator>::value>
    {
    };

    // 萃取某个迭代器的 category
    template <class Iterator>
    typename iterator_traits<Iterator>::iterator_category
        iterator_category(const Iterator&)
    {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }

    // 萃取某个迭代器的 distance_type
    template <class Iterator>
    typename iterator_traits<Iterator>::difference_type*
        distance_type(const Iterator&)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    // 萃取某个迭代器的 value_type
    template <class Iterator>
    typename iterator_traits<Iterator>::value_type*
        value_type(const Iterator&)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    // 以下函数用于计算迭代器间的距离

    // distance 的 input_iterator_tag 的版本
    // 对于输入迭代器，通过逐个递增迭代器来计算距离
    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
        distance_dispatch(InputIterator first, InputIterator last, input_iterator_tag)
    {
        typename iterator_traits<InputIterator>::difference_type n = 0;
        while (first != last)
        {
            ++first;
            ++n;
        }
        return n;
    }

    // distance 的 random_access_iterator_tag 的版本
    // 对于随机访问迭代器，直接通过减法计算距离
    template <class RandomIter>
    typename iterator_traits<RandomIter>::difference_type
        distance_dispatch(RandomIter first, RandomIter last,
            random_access_iterator_tag)
    {
        return last - first;
    }

    // 计算两个迭代器之间的距离
    // 根据迭代器的类别调用相应的 distance_dispatch 函数
    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
        distance(InputIterator first, InputIterator last)
    {
        return distance_dispatch(first, last, iterator_category(first));
    }

    // 以下函数用于让迭代器前进 n 个距离

    // advance 的 input_iterator_tag 的版本
    // 对于输入迭代器，通过逐个递增迭代器来前进 n 个位置
    template <class InputIterator, class Distance>
    void advance_dispatch(InputIterator& i, Distance n, input_iterator_tag)
    {
        while (n--)
            ++i;
    }

    // advance 的 bidirectional_iterator_tag 的版本
    // 对于双向迭代器，根据 n 的正负进行递增或递减操作
    template <class BidirectionalIterator, class Distance>
    void advance_dispatch(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
    {
        if (n >= 0)
            while (n--)  ++i;
        else
            while (n++)  --i;
    }

    // advance 的 random_access_iterator_tag 的版本
    // 对于随机访问迭代器，直接通过加法操作前进 n 个位置
    template <class RandomIter, class Distance>
    void advance_dispatch(RandomIter& i, Distance n, random_access_iterator_tag)
    {
        i += n;
    }

    // 让迭代器前进 n 个位置
    // 根据迭代器的类别调用相应的 advance_dispatch 函数
    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n)
    {
        advance_dispatch(i, n, iterator_category(i));
    }

    /*****************************************************************************************/

    // 模板类 : reverse_iterator
    // 代表反向迭代器，使前进为后退，后退为前进
    template <class Iterator>
    class reverse_iterator
    {
    private:
        // 记录对应的正向迭代器
        Iterator current;

    public:
        // 反向迭代器的五种相应型别
        // 迭代器类别
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        // 指向的数据类型
        typedef typename iterator_traits<Iterator>::value_type        value_type;
        // 迭代距离类型
        typedef typename iterator_traits<Iterator>::difference_type   difference_type;
        // 指针类型
        typedef typename iterator_traits<Iterator>::pointer           pointer;
        // 引用类型
        typedef typename iterator_traits<Iterator>::reference         reference;

        // 正向迭代器类型
        typedef Iterator                                              iterator_type;
        // 反向迭代器自身类型
        typedef reverse_iterator<Iterator>                            self;

    public:
        // 默认构造函数
        reverse_iterator() {}
        // 带参数的构造函数，使用正向迭代器初始化
        explicit reverse_iterator(iterator_type i) :current(i) {}
        // 拷贝构造函数
        reverse_iterator(const self& rhs) :current(rhs.current) {}

    public:
        // 取出对应的正向迭代器
        iterator_type base() const
        {
            return current;
        }

        // 重载操作符

        // 解引用操作符
        // 实际对应正向迭代器的前一个位置
        reference operator*() const
        {
            auto tmp = current;
            return *--tmp;
        }
        // 箭头操作符
        pointer operator->() const
        {
            return &(operator*());
        }

        // 前置递增操作符，前进(++)变为后退(--)
        self& operator++()
        {
            --current;
            return *this;
        }
        // 后置递增操作符，前进(++)变为后退(--)
        self operator++(int)
        {
            self tmp = *this;
            --current;
            return tmp;
        }
        // 前置递减操作符，后退(--)变为前进(++)
        self& operator--()
        {
            ++current;
            return *this;
        }
        // 后置递减操作符，后退(--)变为前进(++)
        self operator--(int)
        {
            self tmp = *this;
            ++current;
            return tmp;
        }

        // 复合赋值操作符 +=
        self& operator+=(difference_type n)
        {
            current -= n;
            return *this;
        }
        // 加法操作符
        self operator+(difference_type n) const
        {
            return self(current - n);
        }
        // 复合赋值操作符 -=
        self& operator-=(difference_type n)
        {
            current += n;
            return *this;
        }
        // 减法操作符
        self operator-(difference_type n) const
        {
            return self(current + n);
        }

        // 下标操作符
        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }
    };

    // 重载 operator-
    // 计算两个反向迭代器之间的距离
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
        operator-(const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    // 重载比较操作符

    // 相等比较操作符
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    // 小于比较操作符
    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() < lhs.base();
    }

    // 不等比较操作符
    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs == rhs);
    }

    // 大于比较操作符
    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return rhs < lhs;
    }

    // 小于等于比较操作符
    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return !(rhs < lhs);
    }

    // 大于等于比较操作符
    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs < rhs);
    }

} // namespace mystl

#endif // !MYTINYSTL_ITERATOR_H_