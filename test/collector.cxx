#include <catch2/catch.hpp>

#include <lv/collector.hxx>

#include <array>
#include <list>
#include <string>
#include <vector>

using namespace std::literals::string_literals;

TEST_CASE("can collect into specified collection", "[collector]")
{
  SECTION("vector")
  {
    std::vector<int> const expected {1, 2, 3, 4};
    auto const numbers = lv::sequence_of({1, 2, 3, 4})
        << lv::collect<std::vector<int>>();
    REQUIRE(numbers == expected);
  }

  SECTION("list")
  {
    std::list<int> const expected {1, 2, 3, 4};
    auto const numbers = lv::sequence_of({1, 2, 3, 4})
        << lv::collect<std::list<int>>();
    REQUIRE(numbers == expected);
  }

  SECTION("string")
  {
    std::string const expected = "hello";
    auto const str = lv::sequence_of({'h', 'e', 'l', 'l', 'o'})
        << lv::collect<std::string>();
    REQUIRE(str == expected);
  }

  SECTION("vector of strings")
  {
    std::vector<std::string> const expected {"foo"s, "bar"s, "baz"s};
    auto const strings = lv::sequence_of({"foo", "bar", "baz"})
        << lv::collect<std::vector<std::string>>();
    REQUIRE(strings == expected);
  }
}

TEST_CASE("can collect into unspecified collection", "[collector]")
{
  using namespace lv;

  SECTION("vector")
  {
    std::vector<int> const expected {1, 2, 3, 4};
    std::vector<int> const numbers = sequence_of({1, 2, 3, 4})
        << collect();
    REQUIRE(numbers == expected);
  }

  SECTION("list")
  {
    std::list<int> const expected {1, 2, 3, 4};
    std::list<int> const numbers = sequence_of({1, 2, 3, 4})
        << collect();
    REQUIRE(numbers == expected);
  }

  SECTION("string")
  {
    std::string const expected = "hello";

    std::vector<char> const input {'h', 'e', 'l', 'l', 'o'};

    std::string const str = sequence_of(input)
        << collect();
    REQUIRE(str == expected);
  }

  SECTION("vector of strings")
  {
    std::vector<std::string> const expected {"foo"s, "bar"s, "baz"s};

    std::array<char const *, 3> const input {"foo", "bar", "baz"};

    std::vector<std::string> const strings = sequence_of(input)
        << collect();

    REQUIRE(strings == expected);
  }
}
