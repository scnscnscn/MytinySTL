#ifndef MYTINYSTL_ALLOC_H_
#define MYTINYSTL_ALLOC_H_

#include <new>
#include <cstddef>
#include <cstdio>
#include <mutex>  

namespace mystl
{
    // 自由链表用于管理内存碎片，分配与回收小内存（<=4K）区块
    union FreeList
    {
        FreeList* next;  // 指向下一个可用的内存区块
        char data[1];    // 储存本块内存的首地址
    };

    // 小对象的最大内存大小，超过此大小将使用 std::malloc 和 std::free
    enum { MaxBytes = 4096 };
    // free lists 的数量
    enum { NumFreelist = 56 };

    // 如果内存需求大于 4096 bytes，直接调用 std::malloc 和 std::free
    // 当内存较小时，以内存池管理，每次配置一大块内存，并维护对应的自由链表
    class alloc
    {
    private:
        static char* start_free;                      // 内存池的起始位置
        static char* end_free;                        // 内存池的结束位置
        static size_t heap_size;                       // 申请 heap 空间附加值大小
        static FreeList* free_list[NumFreelist];  // 自由链表数组，每个链表管理特定大小的内存块
        static std::mutex alloc_mutex;                // 互斥锁，用于线程安全

        // 预分配的内存池大小
        static const size_t PREALLOCATED_SIZE = 128 * 1024; // 128KB

    public:
        // 分配大小为 n 的内存空间
        static void* allocate(size_t n);
        // 释放 p 指向的大小为 n 的内存空间
        static void  deallocate(void* p, size_t n);
        // 重新分配空间，将原大小为 old_size 的空间调整为 new_size
        static void* reallocate(void* p, size_t old_size, size_t new_size);

    private:
        // 内存对齐函数，确定对齐颗粒度
        static size_t M_align(size_t bytes);
        // 上调大小函数， 根据对齐规则调整 bytes 为合适的大小
        static size_t M_round_up(size_t bytes);

        // 根据区块大小，选择对应的 free list 索引
        static size_t M_freelist_index(size_t bytes);
        // 重新填充 free list，当 free list 为空时调用
        static void* M_refill(size_t n);
        // 从内存池中取空间给 free list 使用，条件不允许时，会调整 nblock
        static char* M_chunk_alloc(size_t size, size_t& nblock);
    };

    // 静态成员变量初始化
    char* alloc::start_free = nullptr;
    char* alloc::end_free = nullptr;
    size_t alloc::heap_size = 0;
    FreeList* alloc::free_list[NumFreelist] = { nullptr };
    std::mutex alloc::alloc_mutex;

    // 分配大小为 n 的空间， n > 0
    inline void* alloc::allocate(size_t n)
    {
        std::lock_guard<std::mutex> lock(alloc_mutex); // 加锁保证线程安全
        FreeList* my_free_list;
        FreeList* result;
        if (n > static_cast<size_t>(MaxBytes))
            return std::malloc(n); // 大内存直接使用 std::malloc

        size_t aligned_n = M_round_up(n); // 调整内存大小以满足对齐要求

        my_free_list = free_list[M_freelist_index(aligned_n)]; // 获取对应的自由链表
        result = my_free_list;
        if (result == nullptr)
        {
            void* r = M_refill(aligned_n); // 若链表为空，重新填充
            return r;
        }
        my_free_list = result->next; // 移动链表指针
        return result;
    }

    // 释放 p 指向的大小为 n 的空间
    inline void alloc::deallocate(void* p, size_t n)
    {
        std::lock_guard<std::mutex> lock(alloc_mutex); // 加锁，保证线程安全
        if (n > static_cast<size_t>(MaxBytes))
        {
            std::free(p); // 大内存直接使用 std::free
            return;
        }
        FreeList* q = reinterpret_cast<FreeList*>(p);
        FreeList* my_free_list;
        // 简化的内存对齐和大小调整
        size_t aligned_n = M_round_up(n);
        my_free_list = free_list[M_freelist_index(aligned_n)];
        q->next = my_free_list; // 将释放的内存块插入自由链表头部
        my_free_list = q;
    }

    // 重新分配空间，接受三个参数，参数一为指向新空间的指针，参数二为原来空间的大小，参数三为申请空间的大小
    inline void* alloc::reallocate(void* p, size_t old_size, size_t new_size)
    {
        deallocate(p, old_size); // 释放原空间
        p = allocate(new_size); // 分配新空间
        return p;
    }

    // 对齐函数，根据不同的字节数确定对齐颗粒度
    inline size_t alloc::M_align(size_t bytes)
    {
        return bytes <= 128 ? 8 :
            bytes <= 256 ? 16 :
            bytes <= 512 ? 32 :
            bytes <= 1024 ? 64 :
            bytes <= 2048 ? 128 :
            256;
    }

    // 上调大小函数，将字节数 bytes 向上调整为 align 的整数倍
    inline size_t alloc::M_round_up(size_t bytes)
    {
        size_t align = M_align(bytes);
        return ((bytes + align - 1) & ~(align - 1));
    }

    // free lists 选择函数，根据字节数选择对应的自由链表索引
    inline size_t alloc::M_freelist_index(size_t bytes)
    {
        size_t align = M_align(bytes);
        return (bytes + align - 1) / align - 1;
    }

    // free list 重新填充函数 
    void* alloc::M_refill(size_t n)
    {
        size_t nblock = 10; // 尝试分配 10 个内存块
        char* c = M_chunk_alloc(n, nblock); // 从内存池获取内存块
        FreeList* my_free_list;
        FreeList* result, * cur, * next;
        // 如果只有一个区块，就把这个区块返回给调用者，free list 没有增加新节点
        if (nblock == 1)
            return c;
        // 否则把一个区块给调用者，剩下的纳入 free list 作为新节点
        my_free_list = free_list[M_freelist_index(n)];
        result = (FreeList*)c;
        my_free_list = next = (FreeList*)(c + n);
        for (size_t i = 1; ; ++i)
        {
            cur = next;
            next = (FreeList*)((char*)next + n);
            if (nblock - 1 == i)
            {
                cur->next = nullptr; // 最后一个节点的 next 指针置为 nullptr
                break;
            }
            else
            {
                cur->next = next; // 连接节点
            }
        }
        return result;
    }

    // 从内存池中取空间给 free list 使用，条件不允许时，会调整 nblock
    char* alloc::M_chunk_alloc(size_t size, size_t& nblock)
    {
        char* result;
        size_t need_bytes = size * nblock; // 需要的总字节数
        size_t pool_bytes = end_free - start_free; // 内存池剩余字节数

        if (pool_bytes >= need_bytes)
        {
            result = start_free; // 内存池足够，直接分配
            start_free += need_bytes;
            return result;
        }

        // 如果内存池剩余大小不能完全满足需求量，但至少可以分配一个或一个以上的区块，就返回它
        else if (pool_bytes >= size)
        {
            nblock = pool_bytes / size; // 调整分配的块数
            need_bytes = size * nblock;

            result = start_free;
            start_free += need_bytes;
            return result;
        }

        // 如果内存池剩余大小连一个区块都无法满足
        else
        {
            if (pool_bytes > 0)
            { // 如果内存池还有剩余，把剩余的空间加入到 free list 中
                FreeList* my_free_list = free_list[M_freelist_index(pool_bytes)];
                ((FreeList*)start_free)->next = my_free_list;
                my_free_list = (FreeList*)start_free;
            }
            // 申请 heap 空间
            size_t bytes_to_get = (need_bytes << 1) + M_round_up(heap_size >> 4);
            start_free = (char*)std::malloc(bytes_to_get);

            if (!start_free)
            { // heap 空间也不够
                FreeList* my_free_list, * p;
                // 试着查找有无未用区块，且区块足够大的 free list
                for (size_t i = size; i <= MaxBytes; i += M_align(i))
                {
                    my_free_list = free_list[M_freelist_index(i)];
                    p = my_free_list;
                    if (p)
                    {
                        my_free_list = p->next;
                        start_free = (char*)p;
                        end_free = start_free + i;
                        return M_chunk_alloc(size, nblock);
                    }
                }
                // 记录详细的错误日志，这里简单打印
                std::fprintf(stderr, "Out of memory in allocator.\n");
                end_free = nullptr;
                throw std::bad_alloc();
            }
            end_free = start_free + bytes_to_get;
            heap_size += bytes_to_get;
            return M_chunk_alloc(size, nblock);
        }
    }

}

#endif // !MYTINYSTL_ALLOC_H_    