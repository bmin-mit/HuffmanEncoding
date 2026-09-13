add_executable(huffman_encoding main.cpp)

target_sources(huffman_encoding
        PUBLIC
        FILE_SET CXX_MODULES FILES
        core/core.cppm
        core/core_errors.cppm
)

target_sources(huffman_encoding
        PUBLIC
        FILE_SET CXX_MODULES FILES
        huffman/huffman.cppm
        huffman/huffman_tree.cppm
        huffman/huffman_node.cppm
        huffman/huffman_tree_builder.cppm
)