import std;
import huffman;

int main() {
    auto tree = huffman::buildTreeFromStream(std::cin);

    std::println("{}", *tree.root);

    return 0;
}
