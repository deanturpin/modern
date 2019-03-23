#include <algorithm>
#include <cassert>
#include <future>
#include <iostream>
#include <optional>
#include <vector>

auto main() -> int {

  // Initialiser lists
  // ------------------
  // You used to have to create a vector and then push elements onto it. But
  // with initialiser lists you can populate containers much more concisely.
  std::vector<int> v{1, 2, 3, 4, 5, 6};
  std::vector<int> v1(v);
  std::vector<int> v2 = v;

  // Range-based for loops
  // ------------------
  // We used to have explicit indices or iterators but that can all be cleaned
  // up. Note the use of .at() rather than [] which adds range error
  // protection.
  for (size_t i = 0; i < v1.size(); ++i)
    v1.at(i) += 1;

  for (int &i : v2)
    i += 1;

  // Auto types
  // ------------------
  // The auto keyword is useful in so many places
  auto v3{v};
  for (auto &i : v3)
    i += 1;

  // Lets confirm they're all the same
  assert(v1 == v2);
  assert(v1 == v3);

  // More initialiser lists
  // ------------------
  // Tnere are often make_ routines to build common types but you can also just
  // use an init list.
  const std::pair<int, std::string> p1 = std::make_pair(1, "two");
  const std::pair<int, std::string> p2{1, "two"};

  // Similarly for creating more complex types
  struct S {
    int a;
    int b;
    int c;
  };
  S s{1, 2, 3};

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

  // Optional types
  // ------------------
  // Overcomes the problem of defining a "not initialised" value which
  // inevitably also means something else or you use -1 and accidentally index
  // an array with it. Your functions can return a "not set" or an actual
  // result.

  // Some entries are not initialised to a value
  std::vector<std::optional<long>> options{{}, 1, 2, 3, {}};

  // Print all valid options
  for (const auto &o : options)
    if (o)
      std::cout << o.value() << '\n';

  // Digit separators
  // ------------------
  // If you're defining hardware interfaces then you'll probably have register
  // maps like this.
  const unsigned int reg1{0x1234'5678};

  // Binary literals
  // ------------------
  // You can define things in binary if it's more expressive.
  const unsigned int reg2 = 0b0000'11111'0000'1111;

  // Brace initialers
  // ------------------
  // Brace initialisers take a bit of getting used to but they do give you extra
  // checks. For instance this gives a narrowing warning.
  float narrow{0.1};

  // Move semantics
  // ------------------
  // This is a biggie that you exploit just by moving to C++11 and beyond. The
  // compiler can now choose to move data where previously it would have copied
  // it, potentially giving huge performance benefits.

  // std::quoted
  // std::string_view
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
  // bitset

  // Algorithms
  // std::iota
}
