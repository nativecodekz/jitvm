#include "stdint.h"
#include <stdio.h>
#include <string.h>
#include "allocator.h"

// Определяем тип для нашей функции
typedef void (*jit_func)(uint32_t a, uint32_t b);

void test_func(uint32_t a, uint32_t b) {
    printf("test_func() called with arguments: %d, %d\n", a, b);
}

int main() {

    uint8_t instructions[] = {
            0x55,             // push ebp
            0x48, 0x89, 0xE5, // mov rbp, rsp
            0x89, 0xF0,       // mov eax,esi
            0x89, 0xF2,       // mov edx,esi
            0x01, 0xF8,       // add eax,edi
            0x29, 0xFA,       // sub edx,edi
            0x89, 0xC6,       // mov esi,eax
            0x89, 0xD7,       // mov edi,edx

            0x48, 0xB8,       // mov, rax
            0x00, 0x00, 0x00, 0x00, // вместо этих нулей мы поместим адрес функции. Смещение = 18
            0x00, 0x00, 0x00, 0x00,

            0xFF, 0xD0,       // call rax

            0x5D,             // pop rbp
            0xC3,             // ret
    };

    // Выделяем память под наши инструкции
    void* jit = jit_allocate(sizeof(instructions));

    // Копируем в неё наши инструкции
    memcpy(jit, instructions, sizeof(instructions));

    // Подставляем адрес нашей функции
    *(uintptr_t*)(jit + 18) = (uintptr_t)&test_func;

    // Делаем память исполняемой
    jit_set_executable(jit, sizeof(instructions));

    // Давайте поменяем тип с void* на jit_func
    jit_func func = jit;

    // Теперь мы можем вызвать нашу функцию
    func(5, 12);

    printf("OK\n");
    return 0;
}
