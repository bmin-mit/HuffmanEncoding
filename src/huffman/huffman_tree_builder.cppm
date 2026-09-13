//
// Created by Doan Ngoc Binh Minh on 9/13/26.
//

export module huffman:tree_builder;

import std;
import core;

import :node;
import :tree;

namespace {
    std::array<unsigned long long int, 256> countByteFrequencies(std::istream &stream) {
        std::array<unsigned long long int, 256> frequencies{};

        while (true) {
            std::byte byte{};
            if (!stream.read(reinterpret_cast<char *>(&byte), sizeof(std::byte))) {
                break;
            }
            frequencies.at(static_cast<unsigned char>(byte))++;
        }

        return frequencies;
    }

    struct CompareUniqueNode {
        bool operator()(const std::unique_ptr<huffman::TreeNode> &a,
                        const std::unique_ptr<huffman::TreeNode> &b) const {
            return a->frequency > b->frequency;
        }
    };

    using NodeQueue = std::priority_queue<
        std::unique_ptr<huffman::TreeNode>,
        std::vector<std::unique_ptr<huffman::TreeNode> >,
        CompareUniqueNode
    >;

    NodeQueue createNodeQueue(const std::array<unsigned long long int, 256> &frequencies) {
        NodeQueue sorted_frequencies{};

        for (auto i = 0; i < frequencies.size(); i++) {
            if (frequencies.at(i) == 0) {
                continue;
            }

            sorted_frequencies.push(
                std::make_unique<huffman::TreeNode>(
                    frequencies.at(i),
                    static_cast<std::byte>(i)
                )
            );
        }

        return sorted_frequencies;
    }

    std::unique_ptr<huffman::TreeNode> buildTreeFromQueue(NodeQueue nodeQueue) {
        if (nodeQueue.empty()) {
            throw std::invalid_argument("Cannot build a Huffman tree from empty input");
        }

        while (nodeQueue.size() > 1) {
            auto one = std::move(const_cast<std::unique_ptr<huffman::TreeNode> &>(nodeQueue.top()));
            nodeQueue.pop();
            auto zero = std::move(const_cast<std::unique_ptr<huffman::TreeNode> &>(nodeQueue.top()));
            nodeQueue.pop();

            nodeQueue.push(
                std::make_unique<huffman::TreeNode>(
                    one->frequency + zero->frequency,
                    std::nullopt,
                    std::move(zero),
                    std::move(one)
                )
            );
        };

        return std::move(const_cast<std::unique_ptr<huffman::TreeNode> &>(nodeQueue.top()));
    }
}

export namespace huffman {
    Tree buildTreeFromStream(std::istream &stream) {
        const auto frequencies = countByteFrequencies(stream);
        auto node_queue = createNodeQueue(frequencies);
        auto root = buildTreeFromQueue(std::move(node_queue));

        return Tree(root);
    }
}
