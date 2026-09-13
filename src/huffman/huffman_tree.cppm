//
// Created by Doan Ngoc Binh Minh on 9/13/26.
//

export module huffman:tree;

import std;
import core;

import :node;

export namespace huffman {
    class Tree {
    public:
        const std::unique_ptr<TreeNode> root;

        explicit Tree(std::unique_ptr<TreeNode> &root) : root(std::move(root)) {
        }
    };
}
