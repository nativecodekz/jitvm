#include "allocator.h"
#include <windows.h>

void* exp_jit_allocate(size_t size) {
    SYSTEM_INFO system_info;
    GetSystemInfo(&system_info);
    DWORD page_size = system_info.dwPageSize;

    void* ptr = VirtualAlloc(NULL, (size / page_size + 1) * size, MEM_COMMIT, PAGE_READWRITE);
    return ptr;
}

void exp_jit_set_executable(void* ptr, size_t size) {
    DWORD d;
    VirtualProtect(ptr, size, PAGE_EXECUTE_READ, &d);
}

void exp_jit_free(void* ptr, size_t size) {
    VirtualFree(ptr, 0, MEM_RELEASE);
}