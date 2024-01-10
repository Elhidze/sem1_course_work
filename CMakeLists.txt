cmake_minimum_required(VERSION 3.26)
project(sem1_final)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined -fno-sanitize-recover=all")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address,undefined")

add_executable(sem1_final main.cpp
        io_module.h
        sort_module.h
        book_structure.h
        library_module.h
        io_module.cpp
        book.cpp
        freq_used.h
        freq_used.cpp
        library.cpp
        sort_module.cpp)
