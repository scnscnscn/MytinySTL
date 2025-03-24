#include <iostream>
#include <cassert>
#include "alloc.h"

// 测试内存分配和释放
void test_allocate_and_deallocate() {
    std::cout << "Testing allocate and deallocate..." << std::endl;
    size_t small_size = 10;
    size_t large_size = 5000;

    // 小内存分配和释放
    void* small_ptr = mystl::alloc::allocate(small_size);
    assert(small_ptr != nullptr);
    mystl::alloc::deallocate(small_ptr, small_size);

    // 大内存分配和释放
    void* large_ptr = mystl::alloc::allocate(large_size);
    assert(large_ptr != nullptr);
    mystl::alloc::deallocate(large_ptr, large_size);

    std::cout << "Allocate and deallocate test passed." << std::endl;
}

// 测试内存重新分配
void test_reallocate() {
    std::cout << "Testing reallocate..." << std::endl;
    size_t old_size = 10;
    size_t new_size = 20;

    void* old_ptr = mystl::alloc::allocate(old_size);
    assert(old_ptr != nullptr);

    void* new_ptr = mystl::alloc::reallocate(old_ptr, old_size, new_size);
    assert(new_ptr != nullptr);

    mystl::alloc::deallocate(new_ptr, new_size);

    std::cout << "Reallocate test passed." << std::endl;
}

int main() {
    try {
        test_allocate_and_deallocate();
        test_reallocate();
        std::cout << "All tests passed successfully." << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}