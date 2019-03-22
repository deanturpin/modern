#include <cassert>
#include <iostream>
#include <vector>

auto main() -> int {

  std::cout << "Modern C++ migration\n";

  ////////////////////
  // C++11
  ////////////////////

  // Initialiser lists
  // You used to have to create a vector and then push elements onto it. But
  // with initialiser lists you can populate containers much more concisely.
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  std::vector<int> v1(v);
  std::vector<int> v2 = v;

  // Range-based for loops
  // We used to have explicit indices or iterators but that can all be cleaned
  // up. Note the use of .at() rather than [] which adds range error
  // protection.
  for (size_t i = 0; i < v1.size(); ++i)
    v1.at(i) += 1;

  for (int &i : v2)
    i += 1;

  // Auto types
  // The auto keyword is useful in so many places
  auto v3{v};
  for (auto &i : v3)
    i += 1;

  // Lets confirm they're all the same
  assert(v1 == v2);
  assert(v1 == v3);

  ////////////////////
  // C++14
  ////////////////////

  ////////////////////
  // C++17
  ////////////////////

  // std::optional

  // std::string_view

  // std::async

  // Binary literals

  // Digit separators

  // std::quoted

  // std::clamp

  // std::byte

  // STL algorithms - std::adjacent_difference

  // Raw string literals

  // 64-bit types

  // custom literals - https://en.cppreference.com/w/cpp/language/string_literal

  // override

  // Structured bindings

  // Auto

  // Lambda expressions

  // nullptr

  // Deleted methods

  // Smart pointers

  // Chrono

  // std::filesystem

  // Move semantics

  // bitset

  // References

  // https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/README.md
  //
  // Algorithms
  // std::iota
}
