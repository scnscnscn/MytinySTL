#ifndef MYTINYSTL_ITERATOR_H_
#define MYTINYSTL_ITERATOR_H_

#include <cstddef>
#include "TypeTraits.h"

namespace mystl
{

    // input_iterator_tag: �����������ֻ֧�ֵ���ֻ��������ÿ�ε�����ԭ������ʧЧ��
    struct input_iterator_tag {};
    // output_iterator_tag: �����������ֻ֧�ֵ���ֻд������ÿ�ε�����ԭ������ʧЧ��
    struct output_iterator_tag {};
    // forward_iterator_tag: ǰ���������֧�ֵ����д�������ɶ��ʹ�á�
    struct forward_iterator_tag : public input_iterator_tag {};
    // bidirectional_iterator_tag: ˫���������֧��˫���д������
    struct bidirectional_iterator_tag : public forward_iterator_tag {};
    // random_access_iterator_tag: ������ʵ�������֧��������ʣ��ɽ�������ƫ�Ʋ�����
    struct random_access_iterator_tag : public bidirectional_iterator_tag {};

    // Category: ���������
    // T: ָ�����������
    // Distance: �����������ͣ�Ĭ��Ϊ ptrdiff_t
    // Pointer: ָ�����ͣ�Ĭ��Ϊ T*
    // Reference: �������ͣ�Ĭ��Ϊ T&
    // 
    // ������ȡ���̣���һ���ж��Ƿ���iterator_category
    // �ڶ����ж�iterator_category�Ƿ����ת��
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
        // ������ͨ����ѡ����������İ汾
        struct two { char a; char b; };
        // ͨ�ð汾�������� T û�� iterator_category ��Աʱƥ��˰汾
        template <class U> static two test(...);
        // �ػ��汾�������� T �� iterator_category ��Աʱƥ��˰汾
        template <class U> static char test(typename U::iterator_category* = 0);
    public:
        static const bool value = sizeof(test<T>(0)) == sizeof(char);
    };

    // ������������ȡ��ʵ��ģ��
    // ���ڶ���ģ�����Ϊ false ʱ����������ȡ
    template <class Iterator, bool>
    struct iterator_traits_impl {};

    // ���ڶ���ģ�����Ϊ true ʱ�����е�����������ȡ
    template <class Iterator>
    struct iterator_traits_impl<Iterator, true>
    {
        // ���������
        typedef typename Iterator::iterator_category iterator_category;
        // ָ�����������
        typedef typename Iterator::value_type        value_type;
        // ָ������
        typedef typename Iterator::pointer           pointer;
        // ��������
        typedef typename Iterator::reference         reference;
        // ������������
        typedef typename Iterator::difference_type   difference_type;
    };

    // ������������ȡ�ĸ���ģ��
    // ���ڶ���ģ�����Ϊ false ʱ����������ȡ
    template <class Iterator, bool>
    struct iterator_traits_helper {};

    // ���ڶ���ģ�����Ϊ true ʱ�����ݵ���������Ƿ��ת��Ϊ input_iterator_tag �� output_iterator_tag ������ȡ
    template <class Iterator>
    struct iterator_traits_helper<Iterator, true>
        : public iterator_traits_impl<Iterator,
        std::is_convertible<typename Iterator::iterator_category, input_iterator_tag>::value ||
        std::is_convertible<typename Iterator::iterator_category, output_iterator_tag>::value>
    {
    };

    // ��ȡ������������
    // ͨ�� has_iterator_cat ���������Ƿ��� iterator_category ��Ա��Ȼ����� iterator_traits_helper ������ȡ
    template <class Iterator>
    struct iterator_traits
        : public iterator_traits_helper<Iterator, has_iterator_cat<Iterator>::value> {
    };

    // ���ԭ��ָ���ƫ�ػ��汾
    template <class T>
    struct iterator_traits<T*>
    {
        typedef random_access_iterator_tag           iterator_category;
        typedef T                                    value_type;
        typedef T* pointer;
        typedef T& reference;
        typedef ptrdiff_t                            difference_type;
    };

    // ��Գ���ԭ��ָ���ƫ�ػ��汾
    template <class T>
    struct iterator_traits<const T*>
    {
        typedef random_access_iterator_tag           iterator_category;
        typedef T                                    value_type;
        typedef const T* pointer;
        typedef const T& reference;
        typedef ptrdiff_t                            difference_type;
    };

    // ���������� iterator_category �Ƿ��ת��Ϊָ������ U
    template <class T, class U, bool = has_iterator_cat<iterator_traits<T>>::value>
    struct has_iterator_cat_of
        : public m_bool_constant<std::is_convertible<
        typename iterator_traits<T>::iterator_category, U>::value>
    {
    };

    // ��������û�� iterator_category ��Աʱ������ false
    template <class T, class U>
    struct has_iterator_cat_of<T, U, false> : public m_false_type {};

    // ���������Ƿ�ǡ��Ϊ���������������ǰ���������
    template <class Iter>
    struct is_exactly_input_iterator : public m_bool_constant<has_iterator_cat_of<Iter, input_iterator_tag>::value &&
        !has_iterator_cat_of<Iter, forward_iterator_tag>::value> {
    };

    // ���������Ƿ�Ϊ���������
    template <class Iter>
    struct is_input_iterator : public has_iterator_cat_of<Iter, input_iterator_tag> {};

    // ���������Ƿ�Ϊ���������
    template <class Iter>
    struct is_output_iterator : public has_iterator_cat_of<Iter, output_iterator_tag> {};

    // ���������Ƿ�Ϊǰ�������
    template <class Iter>
    struct is_forward_iterator : public has_iterator_cat_of<Iter, forward_iterator_tag> {};

    // ���������Ƿ�Ϊ˫�������
    template <class Iter>
    struct is_bidirectional_iterator : public has_iterator_cat_of<Iter, bidirectional_iterator_tag> {};

    // ���������Ƿ�Ϊ������ʵ�����
    template <class Iter>
    struct is_random_access_iterator : public has_iterator_cat_of<Iter, random_access_iterator_tag> {};

    // ���������Ƿ�Ϊ��Ч�ĵ�����������������������
    template <class Iterator>
    struct is_iterator :
        public m_bool_constant<is_input_iterator<Iterator>::value ||
        is_output_iterator<Iterator>::value>
    {
    };

    // ��ȡĳ���������� category
    template <class Iterator>
    typename iterator_traits<Iterator>::iterator_category
        iterator_category(const Iterator&)
    {
        typedef typename iterator_traits<Iterator>::iterator_category Category;
        return Category();
    }

    // ��ȡĳ���������� distance_type
    template <class Iterator>
    typename iterator_traits<Iterator>::difference_type*
        distance_type(const Iterator&)
    {
        return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
    }

    // ��ȡĳ���������� value_type
    template <class Iterator>
    typename iterator_traits<Iterator>::value_type*
        value_type(const Iterator&)
    {
        return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
    }

    // ���º������ڼ����������ľ���

    // distance �� input_iterator_tag �İ汾
    // ���������������ͨ������������������������
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

    // distance �� random_access_iterator_tag �İ汾
    // ����������ʵ�������ֱ��ͨ�������������
    template <class RandomIter>
    typename iterator_traits<RandomIter>::difference_type
        distance_dispatch(RandomIter first, RandomIter last,
            random_access_iterator_tag)
    {
        return last - first;
    }

    // ��������������֮��ľ���
    // ���ݵ���������������Ӧ�� distance_dispatch ����
    template <class InputIterator>
    typename iterator_traits<InputIterator>::difference_type
        distance(InputIterator first, InputIterator last)
    {
        return distance_dispatch(first, last, iterator_category(first));
    }

    // ���º��������õ�����ǰ�� n ������

    // advance �� input_iterator_tag �İ汾
    // ���������������ͨ�����������������ǰ�� n ��λ��
    template <class InputIterator, class Distance>
    void advance_dispatch(InputIterator& i, Distance n, input_iterator_tag)
    {
        while (n--)
            ++i;
    }

    // advance �� bidirectional_iterator_tag �İ汾
    // ����˫������������� n ���������е�����ݼ�����
    template <class BidirectionalIterator, class Distance>
    void advance_dispatch(BidirectionalIterator& i, Distance n, bidirectional_iterator_tag)
    {
        if (n >= 0)
            while (n--)  ++i;
        else
            while (n++)  --i;
    }

    // advance �� random_access_iterator_tag �İ汾
    // ����������ʵ�������ֱ��ͨ���ӷ�����ǰ�� n ��λ��
    template <class RandomIter, class Distance>
    void advance_dispatch(RandomIter& i, Distance n, random_access_iterator_tag)
    {
        i += n;
    }

    // �õ�����ǰ�� n ��λ��
    // ���ݵ���������������Ӧ�� advance_dispatch ����
    template <class InputIterator, class Distance>
    void advance(InputIterator& i, Distance n)
    {
        advance_dispatch(i, n, iterator_category(i));
    }

    /*****************************************************************************************/

    // ģ���� : reverse_iterator
    // �������������ʹǰ��Ϊ���ˣ�����Ϊǰ��
    template <class Iterator>
    class reverse_iterator
    {
    private:
        // ��¼��Ӧ�����������
        Iterator current;

    public:
        // �����������������Ӧ�ͱ�
        // ���������
        typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
        // ָ�����������
        typedef typename iterator_traits<Iterator>::value_type        value_type;
        // ������������
        typedef typename iterator_traits<Iterator>::difference_type   difference_type;
        // ָ������
        typedef typename iterator_traits<Iterator>::pointer           pointer;
        // ��������
        typedef typename iterator_traits<Iterator>::reference         reference;

        // �������������
        typedef Iterator                                              iterator_type;
        // �����������������
        typedef reverse_iterator<Iterator>                            self;

    public:
        // Ĭ�Ϲ��캯��
        reverse_iterator() {}
        // �������Ĺ��캯����ʹ�������������ʼ��
        explicit reverse_iterator(iterator_type i) :current(i) {}
        // �������캯��
        reverse_iterator(const self& rhs) :current(rhs.current) {}

    public:
        // ȡ����Ӧ�����������
        iterator_type base() const
        {
            return current;
        }

        // ���ز�����

        // �����ò�����
        // ʵ�ʶ�Ӧ�����������ǰһ��λ��
        reference operator*() const
        {
            auto tmp = current;
            return *--tmp;
        }
        // ��ͷ������
        pointer operator->() const
        {
            return &(operator*());
        }

        // ǰ�õ�����������ǰ��(++)��Ϊ����(--)
        self& operator++()
        {
            --current;
            return *this;
        }
        // ���õ�����������ǰ��(++)��Ϊ����(--)
        self operator++(int)
        {
            self tmp = *this;
            --current;
            return tmp;
        }
        // ǰ�õݼ�������������(--)��Ϊǰ��(++)
        self& operator--()
        {
            ++current;
            return *this;
        }
        // ���õݼ�������������(--)��Ϊǰ��(++)
        self operator--(int)
        {
            self tmp = *this;
            ++current;
            return tmp;
        }

        // ���ϸ�ֵ������ +=
        self& operator+=(difference_type n)
        {
            current -= n;
            return *this;
        }
        // �ӷ�������
        self operator+(difference_type n) const
        {
            return self(current - n);
        }
        // ���ϸ�ֵ������ -=
        self& operator-=(difference_type n)
        {
            current += n;
            return *this;
        }
        // ����������
        self operator-(difference_type n) const
        {
            return self(current + n);
        }

        // �±������
        reference operator[](difference_type n) const
        {
            return *(*this + n);
        }
    };

    // ���� operator-
    // �����������������֮��ľ���
    template <class Iterator>
    typename reverse_iterator<Iterator>::difference_type
        operator-(const reverse_iterator<Iterator>& lhs,
            const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() - lhs.base();
    }

    // ���رȽϲ�����

    // ��ȱȽϲ�����
    template <class Iterator>
    bool operator==(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return lhs.base() == rhs.base();
    }

    // С�ڱȽϲ�����
    template <class Iterator>
    bool operator<(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return rhs.base() < lhs.base();
    }

    // ���ȱȽϲ�����
    template <class Iterator>
    bool operator!=(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs == rhs);
    }

    // ���ڱȽϲ�����
    template <class Iterator>
    bool operator>(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return rhs < lhs;
    }

    // С�ڵ��ڱȽϲ�����
    template <class Iterator>
    bool operator<=(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return !(rhs < lhs);
    }

    // ���ڵ��ڱȽϲ�����
    template <class Iterator>
    bool operator>=(const reverse_iterator<Iterator>& lhs,
        const reverse_iterator<Iterator>& rhs)
    {
        return !(lhs < rhs);
    }

} // namespace mystl

#endif // !MYTINYSTL_ITERATOR_H_