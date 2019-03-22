This is generated from [main.cpp](the source) when it compiles successfully.

# References
- https://github.com/AnthonyCalandra/modern-cpp-features/blob/master/README.md
```c++
#include <algorithm>
#include <cassert>
#include <future>
#include <iostream>
#include <vector>

auto main() -> int {

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

  // More initialiser lists
  // Note the double chevron is parsed correctly now (no need for a space)
  std::vector<std::pair<int, std::string>> x{{1, "two"}, {3, "three"}};

  // Lambda expressions
  // ------------------
  // Think function pointers but a much friendlier implementation
  const auto printer = []() { std::cout << "I am a lambda\n"; };
  printer();

  // You can define them in place as a parameter so you don't have to go hunting
  // for the implementation
  std::for_each(std::cbegin(v), std::cend(v),
                [](const auto &i) { std::cout << i << '\n'; });

  // Threads
  // ------------------
  // Thread are much neater than the old POSIX library but futures
  // are really interesting and let you return the stuff you're interested in
  // much more easily.

  // Define a processor-heavy routine as a lambda
  const auto complicated = []() { return 1; };

  // Push the into the background, note we don't have to actually define what f
  // is thanks to auto
  auto f = std::async(std::launch::async, complicated);

  // Do something else and then block until the data is ready
  f.get();

  ////////////////////
  // C++14
  ////////////////////

  ////////////////////
  // C++17
  ////////////////////

  // std::quoted

  // std::optional
  // std::string_view
  // std::async
  // Binary literals
  // Digit separators
  // std::clamp
  // std::byte
  // STL algorithms - std::adjacent_difference
  // Raw string literals
  // 64-bit types
  // custom literals - https://en.cppreference.com/w/cpp/language/string_literal
  // override
  // Structured bindings
  // nullptr
  // Deleted methods
  // Smart pointers
  // Chrono
  // std::filesystem
  // Move semantics
  // bitset

  // Algorithms
  // std::iota
}
```
