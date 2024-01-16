cmake_minimum_required(VERSION 3.26)
project(sem1_final)

set(CMAKE_CXX_STANDARD 17)

add_executable(sem1_final main.cpp
        sort_module.h
        book_structure.h
        library_module.h
        book.cpp
        freq_used.h
        freq_used.cpp
        library.cpp
        sort_module.cpp)
