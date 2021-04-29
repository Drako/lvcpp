#include <catch2/catch.hpp>

#include <lv/collector.hxx>
#include <lv/mapper.hxx>

#include <array>
#include <map>
#include <sstream>
#include <string>

TEST_CASE("mapping works", "[mapper]")
{
  using namespace lv;

  SECTION("array of ints to string")
  {
    std::string const expected = "hello";
    std::array<int, 5> const input {104, 101, 108, 108, 111};
    std::string const str = sequence_of(input)
        << map([](int chr) { return static_cast<char>(chr); })
        << collect();
    REQUIRE(str == expected);
  }

  SECTION("istringstream to vector of ints doubling values")
  {
    std::vector<int> const expected {2, 4, 6, 8, 10};
    std::istringstream input {"1 2 3 4 5"};
    std::vector<int> const numbers = sequence {
        std::istream_iterator<int> {input},
        std::istream_iterator<int> {}
    }
        << map([](int n) { return n * 2; })
        << collect();
    REQUIRE(numbers == expected);
  }

  SECTION("mapping with generic lambda")
  {
    auto const expected = std::vector {1, 2, 3, 4, 5};
    auto const numbers = sequence_of({2, 4, 6, 8, 10})
        << map([](auto n) { return n / 2; })
        << collect<std::vector<int>>();
    REQUIRE(numbers == expected);
  }

  SECTION("mapping with lambda with capture")
  {
    std::map<int, int> const expected_map_count {{1, 1},
                                                 {2, 1},
                                                 {3, 1}};
    std::map<int, int> map_count;
    auto const expected = std::vector {3, 6, 9};
    auto const numbers = sequence_of({1, 2, 3})
        << map([&map_count](int n) {
          ++map_count[n];
          return n * 3;
        })
        << collect<std::vector<int>>();
    REQUIRE(numbers == expected);
    REQUIRE(map_count == expected_map_count);
  }
}
