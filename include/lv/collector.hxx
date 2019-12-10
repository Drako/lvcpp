#pragma once

#ifndef LVCPP_COLLECTOR_HXX
#define LVCPP_COLLECTOR_HXX

#include <utility>

#include "sequence.hxx"

namespace lv {
  namespace detail {
    struct any_marker
    {
    };

    template <typename Iterator>
    struct collector_proxy
    {
      Iterator begin_;
      Iterator end_;

      constexpr collector_proxy(Iterator && begin, Iterator && end)
          : begin_ {std::forward<Iterator>(begin)}, end_ {std::forward<Iterator>(end)}
      {
      }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "google-explicit-constructor"

      template <typename Collection>
      constexpr operator Collection() const
      {
        return {begin_, end_};
      }

#pragma clang diagnostic pop
    };

    template <typename Collection>
    struct collector
    {
      template <typename Iterator>
      constexpr Collection collect(sequence<Iterator> const & seq) const
      {
        return seq.template collect<Collection>();
      }
    };

    template <>
    struct collector<any_marker>
    {
      template <typename Iterator>
      constexpr collector_proxy<Iterator> collect(sequence<Iterator> const & seq) const
      {
        return {seq.begin(), seq.end()};
      }
    };
  }

  template <typename Iterator, typename Collection>
  constexpr auto operator<<(sequence<Iterator> const & seq, detail::collector<Collection> collector)
  {
    return collector.collect(seq);
  }

  template <typename Collection = detail::any_marker>
  constexpr detail::collector<Collection> collect()
  {
    return {};
  }
}

#endif // LVCPP_COLLECTOR_HXX