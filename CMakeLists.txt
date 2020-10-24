cmake_minimum_required(VERSION 3.17)
project(jitvm C)

set(CMAKE_C_STANDARD 11)

add_executable(jitvm main.c allocator.h allocator_posix.c)