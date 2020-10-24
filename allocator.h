#ifndef JITVM_ALLOCATOR_H
#define JITVM_ALLOCATOR_H

#include <stddef.h>

void* jit_allocate(size_t size);
void jit_set_executable(void* ptr, size_t size);
void jit_free(void* ptr, size_t size);

#endif //JITVM_ALLOCATOR_H
