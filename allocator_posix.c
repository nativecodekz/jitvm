#include "allocator.h"
#include <sys/mman.h>
#include <stdio.h>

/**
 * Аллокатор исполняемой памяти для POSIX систем
 *
 * @param size
 * @return
 */
void* jit_allocate(size_t size) {
    void *ptr = mmap(0, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANON, -1, 0);

    if (ptr == (void*)-1) {
        perror("exp_jit_allocate() error");
        return NULL;
    }

    return ptr;
}


/**
 * Разрешает выполняться коду в памяти
 *
 * @param ptr
 * @param size
 */
void jit_set_executable(void* ptr, size_t size) {
    if (mprotect(ptr, size, PROT_READ | PROT_EXEC) != 0) {
        perror("exp_jit_set_executable() error");
    }
}

/**
 * Деаллокатор памяти
 *
 * @param ptr
 * @param size
 */
void jit_free(void* ptr, size_t size) {
    if (munmap(ptr, size) != 0) {
        perror("exp_jit_free() error");
    }
}