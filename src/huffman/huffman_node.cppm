//
// Created by Doan Ngoc Binh Minh on 9/13/26.
//

export module huffman:node;

import std;

export namespace huffman {
    struct TreeNode {
        const long long unsigned int frequency;
        const std::optional<std::byte> value;
        const std::unique_ptr<TreeNode> zero;
        const std::unique_ptr<TreeNode> one;

        TreeNode(const long long unsigned int frequency,
                 const std::optional<std::byte> value,
                 std::optional<std::unique_ptr<TreeNode> > zero = std::nullopt,
                 std::optional<std::unique_ptr<TreeNode> > one = std::nullopt)
            : frequency(frequency),
              value(value),
              zero(zero ? std::move(*zero) : nullptr),
              one(one ? std::move(*one) : nullptr) {
        }
    };
}

void formatNode(const huffman::TreeNode &node, std::format_context::iterator &out, int depth) {
    std::string indent(depth * 2, ' ');

    if (node.value) {
        std::format_to(out, "{}Leaf(freq={}, value={:#x})\n",
                       indent, node.frequency, std::to_integer<int>(*node.value));
        return;
    }

    std::format_to(out, "{}Node(freq={})\n", indent, node.frequency);

    if (node.zero) {
        formatNode(*node.zero, out, depth + 1);
    } else {
        std::format_to(out, "{}  zero: null\n", indent);
    }

    if (node.one) {
        formatNode(*node.one, out, depth + 1);
    } else {
        std::format_to(out, "{}  one: null\n", indent);
    }
}

export template<>
struct std::formatter<huffman::TreeNode> {
    constexpr auto parse(std::format_parse_context &ctx) {
        return ctx.begin();
    }

    auto format(const huffman::TreeNode &node, std::format_context &ctx) const {
        auto out = ctx.out();
        formatNode(node, out, 0);
        return out;
    }
};
