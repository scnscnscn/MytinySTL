#pragma once
#ifndef  CONSTRUCT_H_
#define  CONSTRUCT_H_

#include <new>
#include "TypeTraits.h"
#include "Iterator.h"
#include "Util.h"

namespace mystl
{

    // construct 构造对象
    //默认构造函数
    template <class Ty>
    void construct(Ty* ptr)
    {
        ::new ((void*)ptr) Ty();
    }
    //使用一个参数
    template <class Ty1, class Ty2>
    void construct(Ty1* ptr, const Ty2& value)
    {
        ::new ((void*)ptr) Ty1(value);
    }
    //可变参数模板
    template <class Ty, class... Args>
    void construct(Ty* ptr, Args&&... args)
    {
        ::new ((void*)ptr) Ty(mystl::forward<Args>(args)...);
    }

    // destroy 将对象析构

    template <class Ty>
    void destroy_one(Ty*, std::true_type) {}

    template <class Ty>
    void destroy_one(Ty* pointer, std::false_type)
    {
        if (pointer != nullptr)
        {
            pointer->~Ty();
        }
    }

    template <class ForwardIter>
    void destroy_cat(ForwardIter, ForwardIter, std::true_type) {}

    template <class ForwardIter>
    void destroy_cat(ForwardIter first, ForwardIter last, std::false_type)
    {
        for (; first != last; ++first)
            destroy(&*first);
    }

    template <class Ty>
    void destroy(Ty* pointer)
    {
        destroy_one(pointer, std::is_trivially_destructible<Ty>{});
    }

    template <class ForwardIter>
    void destroy(ForwardIter first, ForwardIter last)
    {
        destroy_cat(first, last, std::is_trivially_destructible<
            typename iterator_traits<ForwardIter>::value_type>{});
    }

}  

#endif //  CONSTRUCT_H_
