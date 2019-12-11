#include "catch.hpp"

#include <lv/sequence.hxx>

#include <iterator>
#include <string>
#include <vector>

using namespace std::literals::string_literals;

TEST_CASE("sequences can be created from different source types", "[sequence]")
{
  SECTION("C style array")
  {
    int numbers[] = {1, 2, 3};
    auto const seq = lv::sequence_of(numbers);
    REQUIRE(std::cbegin(seq) == std::cbegin(numbers));
    REQUIRE(std::cend(seq) == std::cend(numbers));
    REQUIRE(seq.size() == 3);
  }

  SECTION("initializer list")
  {
    auto const seq = lv::sequence_of({1, 2, 3, 4, 5});
    REQUIRE(seq.size() == 5);
    int expected = 0;
    for (auto const n : seq)
    {
      ++expected;
      REQUIRE(expected == n);
    }
  }

  SECTION("sequence")
  {
    auto const seq1 = lv::sequence_of({1, 2, 3, 4, 5});
    auto const seq2 = lv::sequence_of(seq1);
    REQUIRE(seq2 == seq1);
  }

  SECTION("vector")
  {
    std::vector<int> const numbers {1, 2, 3};
    auto const seq = lv::sequence_of(numbers);
    REQUIRE(std::cbegin(seq) == std::cbegin(numbers));
    REQUIRE(std::cend(seq) == std::cend(numbers));
    REQUIRE(seq.size() == 3);
  }
}

TEST_CASE("sequences can be collected", "[sequence]")
{
  SECTION("vector")
  {
    std::vector<int> const numbers {1, 2, 3, 4, 5};
    auto const collected = lv::sequence_of(numbers).collect<std::vector<int>>();
    REQUIRE(numbers == collected);
  }

  SECTION("string")
  {
    char const text[] = {'h', 'e', 'l', 'l', 'o'};
    auto const collected = lv::sequence_of(text).collect<std::string>();
    REQUIRE("hello"s == collected);
  }

  SECTION("vector of strings")
  {
    std::vector<std::string> const expected {"foo"s, "bar"s, "baz"s};
    auto const strings = lv::sequence_of({"foo", "bar", "baz"})
        .collect<std::vector<std::string>>();
    REQUIRE(strings == expected);
  }
}
