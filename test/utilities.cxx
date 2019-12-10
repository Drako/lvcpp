#include "catch.hpp"

#include <lv/utilities.hxx>

#include <array>
#include <list>
#include <vector>

TEST_CASE("types are determined correctly", "[utilities]")
{
  SECTION("mutable C array")
  {
    int numbers[] = {1, 2, 3};
    auto const it = std::begin(numbers);

    REQUIRE(typeid(std::random_access_iterator_tag) == typeid(lv::category_of<decltype(it)>));
    REQUIRE(typeid(int) == typeid(lv::value_type_of<decltype(it)>));
    REQUIRE(typeid(std::ptrdiff_t) == typeid(lv::difference_type_of<decltype(it)>));
    REQUIRE(typeid(int*) == typeid(lv::pointer_of<decltype(it)>));
    REQUIRE(typeid(int&) == typeid(lv::reference_of<decltype(it)>));
  }

  SECTION("constant C array")
  {
    int const numbers[] = {1, 2, 3};
    auto const it = std::begin(numbers);

    REQUIRE(typeid(std::random_access_iterator_tag) == typeid(lv::category_of<decltype(it)>));
    REQUIRE(typeid(int) == typeid(lv::value_type_of<decltype(it)>));
    REQUIRE(typeid(std::ptrdiff_t) == typeid(lv::difference_type_of<decltype(it)>));
    REQUIRE(typeid(int const *) == typeid(lv::pointer_of<decltype(it)>));
    REQUIRE(typeid(int const &) == typeid(lv::reference_of<decltype(it)>));
  }

  SECTION("mutable C++ array")
  {
    std::array<int, 3> numbers = {1, 2, 3};
    auto const it = std::begin(numbers);

    REQUIRE(typeid(std::random_access_iterator_tag) == typeid(lv::category_of<decltype(it)>));
    REQUIRE(typeid(int) == typeid(lv::value_type_of<decltype(it)>));
    REQUIRE(typeid(std::ptrdiff_t) == typeid(lv::difference_type_of<decltype(it)>));
    REQUIRE(typeid(int*) == typeid(lv::pointer_of<decltype(it)>));
    REQUIRE(typeid(int&) == typeid(lv::reference_of<decltype(it)>));
  }

  SECTION("constant C++ array")
  {
    std::array<int, 3> const numbers = {1, 2, 3};
    auto const it = std::begin(numbers);

    REQUIRE(typeid(std::random_access_iterator_tag) == typeid(lv::category_of<decltype(it)>));
    REQUIRE(typeid(int) == typeid(lv::value_type_of<decltype(it)>));
    REQUIRE(typeid(std::ptrdiff_t) == typeid(lv::difference_type_of<decltype(it)>));
    REQUIRE(typeid(int const *) == typeid(lv::pointer_of<decltype(it)>));
    REQUIRE(typeid(int const &) == typeid(lv::reference_of<decltype(it)>));
  }

  SECTION("mutable vector")
  {
    std::vector<int> numbers {1, 2, 3};
    auto const it = std::begin(numbers);

    REQUIRE(typeid(std::random_access_iterator_tag) == typeid(lv::category_of<decltype(it)>));
    REQUIRE(typeid(int) == typeid(lv::value_type_of<decltype(it)>));
    REQUIRE(typeid(std::ptrdiff_t) == typeid(lv::difference_type_of<decltype(it)>));
    REQUIRE(typeid(int*) == typeid(lv::pointer_of<decltype(it)>));
    REQUIRE(typeid(int&) == typeid(lv::reference_of<decltype(it)>));
  }

  SECTION("constant vector")
  {
    std::vector<int> const numbers {1, 2, 3};
    auto const it = std::begin(numbers);

    REQUIRE(typeid(std::random_access_iterator_tag) == typeid(lv::category_of<decltype(it)>));
    REQUIRE(typeid(int) == typeid(lv::value_type_of<decltype(it)>));
    REQUIRE(typeid(std::ptrdiff_t) == typeid(lv::difference_type_of<decltype(it)>));
    REQUIRE(typeid(int const *) == typeid(lv::pointer_of<decltype(it)>));
    REQUIRE(typeid(int const &) == typeid(lv::reference_of<decltype(it)>));
  }

  SECTION("mutable list")
  {
    std::list<int> numbers {1, 2, 3};
    auto const it = std::begin(numbers);

    REQUIRE(typeid(std::bidirectional_iterator_tag) == typeid(lv::category_of<decltype(it)>));
    REQUIRE(typeid(int) == typeid(lv::value_type_of<decltype(it)>));
    REQUIRE(typeid(std::ptrdiff_t) == typeid(lv::difference_type_of<decltype(it)>));
    REQUIRE(typeid(int*) == typeid(lv::pointer_of<decltype(it)>));
    REQUIRE(typeid(int&) == typeid(lv::reference_of<decltype(it)>));
  }

  SECTION("constant list")
  {
    std::list<int> const numbers {1, 2, 3};
    auto const it = std::begin(numbers);

    REQUIRE(typeid(std::bidirectional_iterator_tag) == typeid(lv::category_of<decltype(it)>));
    REQUIRE(typeid(int) == typeid(lv::value_type_of<decltype(it)>));
    REQUIRE(typeid(std::ptrdiff_t) == typeid(lv::difference_type_of<decltype(it)>));
    REQUIRE(typeid(int const *) == typeid(lv::pointer_of<decltype(it)>));
    REQUIRE(typeid(int const &) == typeid(lv::reference_of<decltype(it)>));
  }
}

TEST_CASE("type traits work as expected", "[utilities]")
{
  SECTION("is_iterator_v")
  {
    REQUIRE(!lv::is_iterator_v<int>);
    REQUIRE(lv::is_iterator_v<int*>);
    REQUIRE(lv::is_iterator_v<int const *>);
    REQUIRE(lv::is_iterator_v<int * const>);
    REQUIRE(lv::is_iterator_v<std::vector<int>::iterator>);
    REQUIRE(lv::is_iterator_v<std::list<int>::iterator>);
  }

  SECTION("is_iterable_v")
  {
    REQUIRE(!lv::is_iterable_v<int>);
    REQUIRE(lv::is_iterable_v<int(&)[10]>);
    REQUIRE(lv::is_iterable_v<std::array<int, 10>>);
    REQUIRE(lv::is_iterable_v<std::vector<int>>);
    REQUIRE(lv::is_iterable_v<std::list<int>>);
  }
}
