# Copilot instructions

## Project overview

This is a C++26 Huffman-encoding project built with CMake 4.3 and LLVM
Clang/libc++. The executable target is `huffman_encoding`, defined in
`src/CMakeLists.txt`. The program currently reads bytes from standard input,
builds a Huffman tree, and exits; encoding/output is not implemented yet.

The implementation uses C++ module interfaces rather than headers:

- `src/core/core.cppm` is the `core` module and re-exports the `core:errors`
  partition.
- `src/core/core_errors.cppm` contains shared core exceptions, including
  `core::NotImplemented`.
- `src/huffman/huffman.cppm` is the public `huffman` module and re-exports
  the node, tree, and tree-builder partitions.
- `src/huffman/huffman_node.cppm` defines the owning `TreeNode` structure.
- `src/huffman/huffman_tree.cppm` defines `huffman::Tree`, which owns the root
  node.
- `src/huffman/huffman_tree_builder.cppm` reads an input stream, counts all
  256 byte values, creates a min-priority queue of nodes, and combines nodes
  into the tree.
- `src/main.cpp` is the executable entry point and imports `std` and
  `huffman`.

When changing a module, update the `FILE_SET CXX_MODULES` entries in
`src/CMakeLists.txt` if a new module interface or partition is added.

## Build and run

The checked-in CMake configuration expects the Homebrew LLVM libc++ module
metadata at `/opt/homebrew/opt/llvm/lib/c++/libc++.modules.json` and uses
`clang++` through that toolchain. Configure and build with:

```sh
cmake -S . -B cmake-build-debug -G Ninja
cmake --build cmake-build-debug --parallel
```

Run the executable with binary input redirected to standard input:

```sh
./cmake-build-debug/src/huffman_encoding < input.bin
```

The current tree-builder implementation has a known build failure when
`buildTreeFromQueue` copies the move-only `std::priority_queue`; preserve
ownership semantics when fixing or extending that code.

## Tests and linting

CTest is the configured test interface:

```sh
ctest --test-dir cmake-build-debug --output-on-failure
```

There are currently no registered tests and no test framework in the
repository. Once tests are added to CTest, run one test by name with:

```sh
ctest --test-dir cmake-build-debug -R '^TestName$' --output-on-failure
```

Use the repository's `.clang-format` for formatting. Check all C++ source and
module files without modifying them with:

```sh
find src -type f \( -name '*.cpp' -o -name '*.cppm' \) -print0 |
  xargs -0 clang-format --dry-run --Werror
```

The `.clang-tidy` configuration enables bugprone, CERT, analyzer,
concurrency, C++ Core Guidelines, misc, modernize, performance, portability,
and readability checks, with selected noisy checks disabled. Run it against a
translation unit using the CMake compilation database:

```sh
clang-tidy -p cmake-build-debug src/main.cpp
```

## Conventions

- Keep public APIs in exported module declarations and use module partitions
  for related implementation units; import project functionality through
  `core` or `huffman` rather than introducing headers.
- Use `std` module imports (`import std;`) and the existing CMake standard
  library module settings instead of adding conventional standard-library
  includes.
- `TreeNode` and `Tree` own their children/root with `std::unique_ptr`; do not
  introduce copying of these types or containers holding them. Move ownership
  explicitly.
- Byte values are represented as `std::byte` and frequencies as unsigned
  integer counts. The tree builder treats `zero` and `one` as the two child
  branches and uses `std::optional` for leaf values.
- Keep helper implementation details in the unnamed namespace in
  `huffman_tree_builder.cppm`; export only the public tree-building function
  from the `huffman` namespace.
- Follow the configured naming rules: lower-case namespaces and variables,
  `CamelCase` classes/structs, `camelBack` functions, and a trailing `_` for
  private members. `.clang-format` is authoritative for the two-space
  indentation and 80-column formatting style.
