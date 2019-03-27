```c++
#include <algorithm>
#include <cassert>
#include <future>
#include <iostream>
#include <optional>
#include <vector>

auto main() -> int {

  // ------------------
  // Auto types
  // ------------------

  // Type inference is a game changer. You can simplify complicated types with
  // auto. But it is a balance of convenience over readability.
  auto x1 = 5u;
  auto x2{0.0};
  auto str{"blah"};

  // And there are some gotchas that arguably wouldn't make it through code
  // review but are perfectly valid code.
  int y1 = 1;
  int &y2 = y1;
  y2 = 2;

  assert(y1 == 2);
  assert(y2 == 2);

  // What do these even point to? (Hint: auto references "decay")
  auto y3 = y2;
  auto &y4 = y2;
  y3 = 3;
  y4 = 4;

  assert(y1 == 4);
  assert(y2 == 4);
  assert(y3 == 3);
  assert(y4 == 4);

  // ------------------
  // Initialiser lists
  // ------------------

  // It was common to create a vector and then push elements onto it (ignoring
  // the potential copy overhead of resizing vectors). But with initialiser
  // lists you can populate containers much more concisely.

  // Let's start with a container
  const std::vector<int> v1{1, 2, 3, 4, 5, 6};

  // Make some copies
  std::vector<int> v2 = v1;
  std::vector<int> v3{v1};

  // Make a copy using auto
  auto v4{v1};

  // Tnere are often "make_" routines to build common types but you can also
  // just use an init list.
  const std::pair<int, std::string> p1 = std::make_pair(1, "two");
  const std::pair<int, std::string> p2{1, "two"};

  // Similarly for creating more complex types.
  struct S {
    int x;
    struct Foo {
      int i;
      int j;
      int a[3];
    } b;
  };

  S s1 = {1, {2, 3, {4, 5, 6}}};

  // ------------------
  // Range-based for loops
  // ------------------

  // Clumsy explicit iterator declarations can be cleaned up with auto.
  // And we can avoid that strange dereferencing idiom.
  for (/* auto */ std::vector<int>::iterator i = v2.begin(); i != v2.end(); ++i)
    *i += 1;

  // Drop the iterators altogether
  for (int &i : v3)
    i += 1;

  // Or even better use auto. Note you don't have access to the current index,
  // which isn't necessarily a bad thing.
  for (auto &i : v4)
    i += 1;

  // Confirm they're all identical
  assert(v1 != v2);
  assert(v2 == v3);
  assert(v2 == v4);

  // ------------------
  // Lambda expressions
  // ------------------

  // Think function pointers but a much friendlier implementation
  const auto printer = []() { std::cout << "I am a lambda\n"; };

  // Call like a regular function
  printer();

  // However, you can define them in place as a parameter so you don't have to
  // go hunting for the implementation. Here's another new for-loop variation
  // too. Note the use of the cbegin routine rather than the method.
  const std::vector<double> d{0.0, 0.1, 0.2};
  std::for_each(std::cbegin(d), std::cend(d),
                [](const auto &i) { std::cout << i << '\n'; });

  // ------------------
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
  std::cout << f.get() << '\n';

  // ------------------
  // Smart pointers
  // ------------------

  // You no longer need to use new and delete explicitly. Smart pointers clean
  // up after themselves when they go out of scope: Resource Allocation Is
  // Initialistion (RAII).

  // ------------------
  // Optional types
  // ------------------

  // These overcome the problem of defining a "not initialised" value which
  // inevitably also means something else or you use -1 and accidentally index
  // an array with it. Your functions can return a "not set" or an actual
  // result.

  // Some entries are not initialised to a value
  std::vector<std::optional<long>> options;
  options.push_back({});
  options.push_back(1);
  options.push_back(2);
  options.push_back(3);
  options.push_back({});

  // Print all valid options
  for (const auto &o : options)
    if (o)
      std::cout << o.value() << '\n';

  // ------------------
  // Digit separators
  // ------------------

  // If you're defining hardware interfaces then you'll probably have register
  // maps like this.
  const unsigned int reg1{0x1234'5678};

  // ------------------
  // Binary literals
  // ------------------

  // You can even define things in binary if it's more expressive. And also use
  // types with explicit size.
  const uint32_t reg2 = 0b0000'11111'0000'1111;

  // ------------------
  // Brace initialers
  // ------------------

  // Brace initialisers take a bit of getting used to but they do give you extra
  // checks. For instance this gives a narrowing warning.
  const float narrow{0.1};

  // ------------------
  // Move semantics
  // ------------------

  // This is a biggie that you exploit just by moving to C++11 and beyond. The
  // compiler can now choose to move data where previously it would have copied
  // it, potentially giving huge performance benefits.

  // std::quoted
  // std::for_each
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

  // C++2a (what will become C++20)
  // three-way comparison using the "spaceship operator", operator <=>
  // designated initializers
  // Software transactional memory
}
```
