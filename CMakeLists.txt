cmake_minimum_required(VERSION 4.3)
project(img C)

set(CMAKE_C_STANDARD 99)

add_executable(img src/img.c
        src/types.h
        src/codecs/codecs.c
        src/codecs/codecs.h
        src/codecs/v2.0.h
        src/converting.c
        src/converting.h)
target_include_directories(img PUBLIC ./include)