#ifndef MYTINYSTL_TYPE_TRAITS_H_
#define MYTINYSTL_TYPE_TRAITS_H_
#include "type_traits"
namespace mystl {
    // ����ѡ�����ṹ��
    template<bool Condition, class ThenType, class ElseType>
    struct IfThenElse;

    template<class ThenType, class ElseType>
    struct IfThenElse<true, ThenType, ElseType> {
        using result = ThenType;
    };

    template<class ThenType, class ElseType>
    struct IfThenElse<false, ThenType, ElseType> {
        using result = ElseType;
    };

    // ���� true_type �� false_type �ṹ��
    struct _true_type {};
    struct _false_type {};

    // ������ȡ��ģ��
    template<class T>
    struct _type_traits {
        typedef _false_type has_trivial_default_constructor;
        typedef _false_type has_trivial_copy_constructor;
        typedef _false_type has_trivial_assignment_operator;
        typedef _false_type has_trivial_destructor;
        typedef _false_type is_POD_type;
    };

    // �������͵��ػ�
    template<>
    struct _type_traits<bool> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<char> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<unsigned char> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<signed char> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<wchar_t> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<short> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<unsigned short> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<int> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<unsigned int> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<long> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<unsigned long> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<long long> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<unsigned long long> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<float> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<double> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<long double> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    // ָ�����͵��ػ�
    template<class T>
    struct _type_traits<T*> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<class T>
    struct _type_traits<const T*> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<char*> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<unsigned char*> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<signed char*> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<const char*> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<const unsigned char*> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    template<>
    struct _type_traits<const signed char*> {
        typedef _true_type has_trivial_default_constructor;
        typedef _true_type has_trivial_copy_constructor;
        typedef _true_type has_trivial_assignment_operator;
        typedef _true_type has_trivial_destructor;
        typedef _true_type is_POD_type;
    };

    // �����ṹ�� m_integral_constant �����������
    template <class T, T v>
    struct m_integral_constant {
        static constexpr T value = v;
    };

    template <bool b>
    using m_bool_constant = m_integral_constant<bool, b>;

    typedef m_bool_constant<true>  m_true_type;
    typedef m_bool_constant<false> m_false_type;
 
 
} // namespace mystl

#endif // !MYTINYSTL_TYPE_TRAITS_H_