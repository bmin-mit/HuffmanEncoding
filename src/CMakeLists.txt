add_executable(huffman_encoding main.cpp)

target_sources(huffman_encoding
        PRIVATE
        core/core.cpp
        PUBLIC
        FILE_SET CXX_MODULES FILES
        core/core.ixx
)

target_sources(huffman_encoding
        PRIVATE
        huffman/huffman.cpp
        PUBLIC
        FILE_SET CXX_MODULES FILES
        huffman/huffman.ixx
)