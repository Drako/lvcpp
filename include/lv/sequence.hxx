#pragma once

#ifndef LVCPP_SEQUENCE_HXX
#define LVCPP_SEQUENCE_HXX

#include <initializer_list>
#include <iterator>
#include <type_traits>

#include "utilities.hxx"

namespace lv {
  template <typename Iterator>
  struct sequence
  {
    using size_type = difference_type_of<Iterator>;

    Iterator begin_;
    Iterator end_;

    template <typename Collection>
    [[nodiscard]]
    constexpr auto collect() const
    -> std::enable_if_t<std::is_constructible_v<Collection, Iterator, Iterator>, Collection>
    {
      return {begin_, end_};
    }

    [[nodiscard]]
    constexpr Iterator begin() const
    {
      return begin_;
    }

    [[nodiscard]]
    constexpr Iterator end() const
    {
      return end_;
    }

    [[nodiscard]]
    constexpr size_type size() const
    {
      return std::distance(begin_, end_);
    }

    [[nodiscard]]
    constexpr bool empty() const
    {
      return begin_ == end_;
    }

    [[nodiscard]]
    constexpr bool operator==(sequence const & rhs) const
    {
      for (auto lit = begin_, rit = rhs.begin_; lit != end_ && rit != rhs.end_; ++lit, ++rit)
        if (*lit != *rit)
          return false;
      return true;
    }

    [[nodiscard]]
    constexpr bool operator!=(sequence const & rhs) const
    {
      return !(*this == rhs);
    }
  };

  template <typename Iterator>
  sequence(Iterator, Iterator) -> sequence<Iterator>;

  template <typename Iterable>
  constexpr auto sequence_of(Iterable const & iterable)
  -> std::enable_if_t<is_iterable_v<Iterable>, sequence<decltype(std::cbegin(iterable))>>
  {
    return {std::cbegin(iterable), std::cend(iterable)};
  }

  template <typename Item, std::size_t Size>
  constexpr auto sequence_of(Item (& arr)[Size])
  -> sequence<Item const *>
  {
    return {arr + 0, arr + Size};
  }

  template <typename Item>
  constexpr auto sequence_of(std::initializer_list<Item> const & items)
  -> sequence<decltype(std::cbegin(items))>
  {
    return {std::cbegin(items), std::cend(items)};
  }
}

#endif // LVCPP_SEQUENCE_HXX
