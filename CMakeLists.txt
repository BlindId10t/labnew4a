cmake_minimum_required(VERSION 3.16)
project(labnew4 C)

set(CMAKE_C_STANDARD 99)

add_executable(labnew4 main.c tree.h dialog.c dialog.h time.h base.h base.c time.c add.c add.h)

