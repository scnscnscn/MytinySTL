#ifndef MYTINYSTL_ALLOC_H_
#define MYTINYSTL_ALLOC_H_

#include <new>
#include <cstddef>
#include <cstdio>
#include <mutex>  

namespace mystl
{
    // �����������ڹ����ڴ���Ƭ�����������С�ڴ棨<=4K������
    union FreeList
    {
        FreeList* next;  // ָ����һ�����õ��ڴ�����
        char data[1];    // ���汾���ڴ���׵�ַ
    };

    // С���������ڴ��С�������˴�С��ʹ�� std::malloc �� std::free
    enum { MaxBytes = 4096 };
    // free lists ������
    enum { NumFreelist = 56 };

    // ����ڴ�������� 4096 bytes��ֱ�ӵ��� std::malloc �� std::free
    // ���ڴ��Сʱ�����ڴ�ع���ÿ������һ����ڴ棬��ά����Ӧ����������
    class alloc
    {
    private:
        static char* start_free;                      // �ڴ�ص���ʼλ��
        static char* end_free;                        // �ڴ�صĽ���λ��
        static size_t heap_size;                       // ���� heap �ռ丽��ֵ��С
        static FreeList* free_list[NumFreelist];  // �����������飬ÿ����������ض���С���ڴ��
        static std::mutex alloc_mutex;                // �������������̰߳�ȫ

        // Ԥ������ڴ�ش�С
        static const size_t PREALLOCATED_SIZE = 128 * 1024; // 128KB

    public:
        // �����СΪ n ���ڴ�ռ�
        static void* allocate(size_t n);
        // �ͷ� p ָ��Ĵ�СΪ n ���ڴ�ռ�
        static void  deallocate(void* p, size_t n);
        // ���·���ռ䣬��ԭ��СΪ old_size �Ŀռ����Ϊ new_size
        static void* reallocate(void* p, size_t old_size, size_t new_size);

    private:
        // �ڴ���뺯����ȷ�����������
        static size_t M_align(size_t bytes);
        // �ϵ���С������ ���ݶ��������� bytes Ϊ���ʵĴ�С
        static size_t M_round_up(size_t bytes);

        // ���������С��ѡ���Ӧ�� free list ����
        static size_t M_freelist_index(size_t bytes);
        // ������� free list���� free list Ϊ��ʱ����
        static void* M_refill(size_t n);
        // ���ڴ����ȡ�ռ�� free list ʹ�ã�����������ʱ������� nblock
        static char* M_chunk_alloc(size_t size, size_t& nblock);
    };

    // ��̬��Ա������ʼ��
    char* alloc::start_free = nullptr;
    char* alloc::end_free = nullptr;
    size_t alloc::heap_size = 0;
    FreeList* alloc::free_list[NumFreelist] = { nullptr };
    std::mutex alloc::alloc_mutex;

    // �����СΪ n �Ŀռ䣬 n > 0
    inline void* alloc::allocate(size_t n)
    {
        std::lock_guard<std::mutex> lock(alloc_mutex); // ������֤�̰߳�ȫ
        FreeList* my_free_list;
        FreeList* result;
        if (n > static_cast<size_t>(MaxBytes))
            return std::malloc(n); // ���ڴ�ֱ��ʹ�� std::malloc

        size_t aligned_n = M_round_up(n); // �����ڴ��С���������Ҫ��

        my_free_list = free_list[M_freelist_index(aligned_n)]; // ��ȡ��Ӧ����������
        result = my_free_list;
        if (result == nullptr)
        {
            void* r = M_refill(aligned_n); // ������Ϊ�գ��������
            return r;
        }
        my_free_list = result->next; // �ƶ�����ָ��
        return result;
    }

    // �ͷ� p ָ��Ĵ�СΪ n �Ŀռ�
    inline void alloc::deallocate(void* p, size_t n)
    {
        std::lock_guard<std::mutex> lock(alloc_mutex); // ��������֤�̰߳�ȫ
        if (n > static_cast<size_t>(MaxBytes))
        {
            std::free(p); // ���ڴ�ֱ��ʹ�� std::free
            return;
        }
        FreeList* q = reinterpret_cast<FreeList*>(p);
        FreeList* my_free_list;
        // �򻯵��ڴ����ʹ�С����
        size_t aligned_n = M_round_up(n);
        my_free_list = free_list[M_freelist_index(aligned_n)];
        q->next = my_free_list; // ���ͷŵ��ڴ�������������ͷ��
        my_free_list = q;
    }

    // ���·���ռ䣬������������������һΪָ���¿ռ��ָ�룬������Ϊԭ���ռ�Ĵ�С��������Ϊ����ռ�Ĵ�С
    inline void* alloc::reallocate(void* p, size_t old_size, size_t new_size)
    {
        deallocate(p, old_size); // �ͷ�ԭ�ռ�
        p = allocate(new_size); // �����¿ռ�
        return p;
    }

    // ���뺯�������ݲ�ͬ���ֽ���ȷ�����������
    inline size_t alloc::M_align(size_t bytes)
    {
        return bytes <= 128 ? 8 :
            bytes <= 256 ? 16 :
            bytes <= 512 ? 32 :
            bytes <= 1024 ? 64 :
            bytes <= 2048 ? 128 :
            256;
    }

    // �ϵ���С���������ֽ��� bytes ���ϵ���Ϊ align ��������
    inline size_t alloc::M_round_up(size_t bytes)
    {
        size_t align = M_align(bytes);
        return ((bytes + align - 1) & ~(align - 1));
    }

    // free lists ѡ�����������ֽ���ѡ���Ӧ��������������
    inline size_t alloc::M_freelist_index(size_t bytes)
    {
        size_t align = M_align(bytes);
        return (bytes + align - 1) / align - 1;
    }

    // free list ������亯�� 
    void* alloc::M_refill(size_t n)
    {
        size_t nblock = 10; // ���Է��� 10 ���ڴ��
        char* c = M_chunk_alloc(n, nblock); // ���ڴ�ػ�ȡ�ڴ��
        FreeList* my_free_list;
        FreeList* result, * cur, * next;
        // ���ֻ��һ�����飬�Ͱ�������鷵�ظ������ߣ�free list û�������½ڵ�
        if (nblock == 1)
            return c;
        // �����һ������������ߣ�ʣ�µ����� free list ��Ϊ�½ڵ�
        my_free_list = free_list[M_freelist_index(n)];
        result = (FreeList*)c;
        my_free_list = next = (FreeList*)(c + n);
        for (size_t i = 1; ; ++i)
        {
            cur = next;
            next = (FreeList*)((char*)next + n);
            if (nblock - 1 == i)
            {
                cur->next = nullptr; // ���һ���ڵ�� next ָ����Ϊ nullptr
                break;
            }
            else
            {
                cur->next = next; // ���ӽڵ�
            }
        }
        return result;
    }

    // ���ڴ����ȡ�ռ�� free list ʹ�ã�����������ʱ������� nblock
    char* alloc::M_chunk_alloc(size_t size, size_t& nblock)
    {
        char* result;
        size_t need_bytes = size * nblock; // ��Ҫ�����ֽ���
        size_t pool_bytes = end_free - start_free; // �ڴ��ʣ���ֽ���

        if (pool_bytes >= need_bytes)
        {
            result = start_free; // �ڴ���㹻��ֱ�ӷ���
            start_free += need_bytes;
            return result;
        }

        // ����ڴ��ʣ���С������ȫ�����������������ٿ��Է���һ����һ�����ϵ����飬�ͷ�����
        else if (pool_bytes >= size)
        {
            nblock = pool_bytes / size; // ��������Ŀ���
            need_bytes = size * nblock;

            result = start_free;
            start_free += need_bytes;
            return result;
        }

        // ����ڴ��ʣ���С��һ�����鶼�޷�����
        else
        {
            if (pool_bytes > 0)
            { // ����ڴ�ػ���ʣ�࣬��ʣ��Ŀռ���뵽 free list ��
                FreeList* my_free_list = free_list[M_freelist_index(pool_bytes)];
                ((FreeList*)start_free)->next = my_free_list;
                my_free_list = (FreeList*)start_free;
            }
            // ���� heap �ռ�
            size_t bytes_to_get = (need_bytes << 1) + M_round_up(heap_size >> 4);
            start_free = (char*)std::malloc(bytes_to_get);

            if (!start_free)
            { // heap �ռ�Ҳ����
                FreeList* my_free_list, * p;
                // ���Ų�������δ�����飬�������㹻��� free list
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
                // ��¼��ϸ�Ĵ�����־������򵥴�ӡ
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