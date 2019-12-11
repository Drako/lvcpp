#pragma once

#ifndef LVCPP_MAPPER_HXX
#define LVCPP_MAPPER_HXX

#include <optional>
#include <type_traits>

#include "sequence.hxx"

namespace lv {
  namespace detail {
    template <typename Function>
    struct mapper
    {
      Function const & function_;
    };

    template <typename BaseIterator, typename Function>
    struct mapping_iterator
    {
      using iterator_category = category_of<BaseIterator>;
      using value_type = std::invoke_result_t<Function, ::lv::value_type_of<BaseIterator>>;
      using difference_type = difference_type_of<BaseIterator>;
      using reference = value_type const &;
      using pointer = value_type const *;

    private:
      BaseIterator current_;
      mutable std::optional<value_type> cached_value_;
      Function const & function_;

      constexpr pointer mapped_value() const
      {
        if (!cached_value_)
          cached_value_ = function_(*current_);
        return cached_value_.operator->();
      }

    public:
      constexpr mapping_iterator(BaseIterator current, Function const & function)
          : current_ {current}, cached_value_ {}, function_ {function}
      {}

      constexpr mapping_iterator(mapping_iterator const &) = default;

      constexpr mapping_iterator(mapping_iterator &&)
      noexcept(std::is_nothrow_move_constructible_v<BaseIterator> &&
               std::is_nothrow_move_constructible_v<std::optional<value_type>>) = default;

      constexpr mapping_iterator & operator=(mapping_iterator const &) = default;

      constexpr mapping_iterator & operator=(mapping_iterator &&)
      noexcept(std::is_nothrow_move_assignable_v<BaseIterator> &&
               std::is_nothrow_move_assignable_v<std::optional<value_type>>) = default;

      ~mapping_iterator() = default;

      constexpr bool operator==(mapping_iterator const & rhs) const
      {
        return current_ == rhs.current_;
      }

      constexpr bool operator!=(mapping_iterator const & rhs) const
      {
        return current_ != rhs.current_;
      }

      constexpr mapping_iterator & operator++()
      {
        current_ = std::next(current_);
        cached_value_.reset();
        return *this;
      }

      template <typename Category = iterator_category>
      constexpr auto operator--()
      -> std::enable_if_t<std::is_base_of_v<std::bidirectional_iterator_tag, Category>, mapping_iterator &>
      {
        current_ = std::prev(current_);
        cached_value_.reset();
        return *this;
      }

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cert-dcl21-cpp"

      constexpr mapping_iterator operator++(int) &
      {
        auto const old = *this;
        ++(*this);
        return old;
      }

      template <typename Category = iterator_category>
      constexpr auto operator--(int) &
      -> std::enable_if_t<std::is_base_of_v<std::bidirectional_iterator_tag, Category>, mapping_iterator>
      {
        auto const old = *this;
        --(*this);
        return old;
      }

#pragma clang diagnostic pop

      constexpr reference operator*() const
      {
        return *mapped_value();
      }

      constexpr pointer operator->() const
      {
        return mapped_value();
      }

      constexpr difference_type operator-(mapping_iterator const & rhs) const
      {
        return std::distance(rhs.current_, current_);
      }
    };
  }

  template <typename Function>
  constexpr detail::mapper<Function> map(Function const & function)
  {
    return {function};
  }

  template <typename Iterator, typename Function>
  constexpr auto operator<<(::lv::sequence<Iterator> const & seq, detail::mapper<Function> const & m)
  {
    return sequence {
        detail::mapping_iterator<Iterator, Function> {seq.begin(), m.function_},
        detail::mapping_iterator<Iterator, Function> {seq.end(), m.function_},
    };
  }
}

#endif // LVCPP_MAPPER_HXX
