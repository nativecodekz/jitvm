cmake_minimum_required(VERSION 3.17)
project(jitvm C)

set(CMAKE_C_STANDARD 11)

# Здесь мы просто в зависимости от целевой системы (Windows или Linux/Mac OS) выбираем нужные исходники
if (WIN32)
    set(WIN_SOURCES allocator_win.c)
else()
    set(POSIX_SOURCES allocator_posix.c)
endif()

add_executable(jitvm main.c allocator.h ${WIN_SOURCES} ${POSIX_SOURCES})