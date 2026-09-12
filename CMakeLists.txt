cmake_minimum_required(VERSION 4.3)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "451f2fe2-a8a2-47c3-bc32-94786d8fc91b")

project(huffman_encoding)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_MODULE_STD ON)
set(CMAKE_CXX_STDLIB_MODULES_JSON /opt/homebrew/opt/llvm/lib/c++/libc++.modules.json)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_subdirectory(src)
