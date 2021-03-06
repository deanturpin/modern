```c++
#include <algorithm>
#include <cassert>
#include <chrono>
#include <complex>
#include <deque>
#include <future>
#include <iostream>
#include <list>
#include <optional>
#include <utility>
#include <vector>

int main() {

  // Auto types
  //
  // Type inference is a game changer. Essentially you can simplify
  // complicated (or unknown) type declarations with auto. But it is a balance
  // of convenience over readability.

  auto x1 = 5;

  std::vector<std::string> moon = {"Don't", "look", "at", "the", "finger"};
  auto finger                   = moon.front();

  // However, there are a few perfectly valid gotchas that arguably wouldn't
  // make it through code review. Let's create a variable and a reference to
  // it.
  int y1  = 1;
  int &y2 = y1;

  // So updating y2 actually updates y1.
  y2 = 2;

  assert(y1 == 2);
  assert(y2 == 2);

  // But how does auto deal with references? Do you get another reference or a
  // copy? (Hint: auto "decays" to the base type - no consts, no refs).
  auto y3  = y2;
  auto &y4 = y2;
  y3       = 3;
  y4       = 4;

  assert(y1 == 4);
  assert(y2 == 4);
  assert(y3 == 3);
  assert(y4 == 4);

  // Brace initialers
  //
  // These take a bit of getting used to but they do give you extra checks.
  // For example the compiler coughs a narrowing warning for the following.
  // The "moon" vector above we could have equally declared without the "=".
  double wide{1.0};
  float narrow{wide};

  assert(sizeof narrow == 4);
  assert(sizeof wide == 8);

  // Initialiser lists
  //
  // We used to create a vector and then push elements onto it (ignoring the
  // potential copy overhead of resizing vectors). But with initialiser lists
  // you can populate containers much more concisely.

  // Initialise a container
  std::list<int> v1{1, 2, 3, 4, 5, 6};

  // Initialise a std::pair
  std::pair<int, std::string> p1{1, "two"};

  // Initialise complex types
  struct S {
    int x;
    struct Foo {
      int i;
      int j;
      int a[3];
    } b;
  };

  S s1 = {1, {2, 3, {4, 5, 6}}};

  // Range-based for loops
  //
  // Clumsy explicit iterator declarations can be cleaned up with auto.

  // Let's make some copies of v1 to work with
  std::list<int> v2 = v1;
  std::list<int> v3{v1};
  auto v4{v1};

  // So this:
  /*
  for (std::list<int>::iterator i = v2.begin(); i != v2.end(); ++i)
      *i += 1;
  */

  // Becomes this:
  for (auto i = v2.begin(); i != v2.end(); ++i)
    *i += 1;

  // In fact we can drop the iterators altogether and also avoid that strange
  // dereferencing idiom.
  for (int &i : v3)
    i += 1;

  // Or even use auto. Note you don't have access to the current index, which
  // isn't necessarily a bad thing.
  for (auto &i : v4)
    i += 1;

  // Confirm the various for-loops do the same thing.
  assert(v1 != v2);
  assert(v2 == v3);
  assert(v2 == v4);

  // Lambda expressions
  //
  // Think function pointers but a much friendlier implementation. Call like a
  // regular function or pass them as a parameter. You can also define them
  // in-place so you don't have to go hunting for the implementation like you
  // might if you passed a function name. Here's another new for-loop
  // variation too. Note the use of the cbegin routine rather than the method.
  const auto printer = []() { std::cout << "I am a first-class citizen\n"; };

  // Call like a function
  printer();

  // In-place lambda definition
  const std::vector<double> d{0.0, 0.1, 0.2};
  std::for_each(std::cbegin(d), std::cend(d),
                [](const auto &i) { std::cout << i << '\n'; });

  // Threads
  //
  // Thread are much neater than the old POSIX library but futures are really
  // interesting and let you return the stuff you're interested in much more
  // easily.

  // Define a processor-heavy routine as a lambda. Here the return has been
  // declared explicitly.
  const auto complicated = []() { return 1; };

  // Push the into the background, note we don't have to actually define what
  // f is thanks to auto. It's actually a std::future<int>
  auto f = std::async(std::launch::async, complicated);

  // Do something else and then block until the data is ready. We could change
  // the return type of complicated() and nothing else needs to change.
  std::cout << f.get() << '\n';

  // Optional types
  //
  // This overcomes the problem of defining a "not initialised" value which is
  // inevitably used to index an array. Your functions can also effectively
  // return a "no result".

  // Create a container with some default entries
  std::deque<std::optional<long>> options{0, 1, 2, 3, 4};
  assert(options.size() == 5);

  // Make the one at the back undefined
  options.back() = {};

  // Count the valid entries with the help of a lambda expression
  const auto c = std::count_if(std::cbegin(options), std::cend(options),
                               [](const auto &o) { return o; });

  assert(c == 4);

  // Digit separators
  //
  // If you're defining hardware interfaces then you'll probably have register
  // maps like this. Using digit separators could help improve readability in
  // some cases.
  int reg1    = 0x5692a5b6;
  int reg2    = 0x5692'a5b6;
  double reg3 = 1'000.000'001;

  assert(reg1 == reg2);

  // You can even define things in binary if it's clearer. And also specify
  // the size of a type explicitly.
  const uint32_t netmask{0b11111111'11111111'11111111'00000000};

  assert(netmask == 0xff'ff'ff'00);
  assert(sizeof netmask == 4);

  // Type alias
  //
  // Create type-safe typedefs with "using". Note the trailing cluster of
  // angle-brackets are parsed correctly in C++11 (no need to insert spaces).
  using container_t = std::vector<std::pair<std::string, std::string>>;
  container_t safe;

  // Structured bindings
  //
  // You might declare intermediate variables to make the first/second more
  // meaningful below.
  std::pair<std::string, std::string> chuckle{"to me", "to you"};
  std::cout << chuckle.first << ", " << chuckle.second << '\n';

  // But now you can do it in one expression with structured bindings.
  auto [barry, paul] = chuckle;
  std::cout << barry << ", " << paul << '\n';

  // Standard literals
  using namespace std::complex_literals;
  using namespace std::string_literals;
  using namespace std::chrono_literals;

  auto z   = 1i;             // auto deduces complex<double>
  auto str = "hello world"s; // auto deduces string
  auto dur = 60s;            // auto deduces chrono::seconds

  // Or if you want all the literals.
  // using namespace std::literals;

  // Tuples
  //
  // Like pairs but better. Arbitrary collection of heterogenous types. You can
  // retrieve values by index (which looks a bit odd) or by type!
  std::tuple<std::string, double, int> h1{"one", 2.0, 3};
  std::cout << std::get<std::string>(h1) << ' ' << std::get<0>(h1) << ' '
            << std::get<double>(h1) << '\n';

  // byte
  //
  // When you really want something to be a byte and not something that looks a
  // bit like a char.
  std::byte b1{4};

  // Exchanging values
  //
  // Replace that old declare a temp variable idiom with an atomic update.
  // std::exchange also returns the original value.
  int current  = 5;
  int previous = std::exchange(current, 6);

  // Things to remove
  //
  // inline - just let the compiler decide what should be inlined. It will
  // probably ignore you anyway.

  // Move semantics
  //
  // This is a biggie that you exploit just by moving to C++11 and beyond. The
  // compiler can now choose to move data where previously it would have
  // copied it, potentially giving huge performance benefits.

  // Smart pointers
  //
  // You no longer need to use new and delete explicitly. Smart pointers clean
  // up after themselves when they go out of scope: Resource Allocation Is
  // Initialistion (RAII).

  // ---------------------------------------------------------------------------

  // double operator "" _Hz(double);
  // long double operator "" _w(long double);
  // std::cout << 10_Hz << '\n';
  // auto l = 20_w;
  // using std::operator ""s

  // std::quoted
  // std::string_view
  // std::clamp
  // Raw string literals
  // 64-bit types
  // User literals
  // Lambda captures
  // https://en.cppreference.com/w/cpp/language/string_literal override
  // nullptr
  // Deleted methods
  // Smart pointers
  // Chrono
  // std::filesystem
  // bitset
  // static_assert

  // Algorithms
  //
  // std::iota
  // std::adjacent_difference

  // C++2a (what will become C++20)
  // three-way comparison using the "spaceship operator", operator <=>
  // designated initializers
  // Software transactional memory
}
```
