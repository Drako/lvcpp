#pragma once

#ifndef LVCPP_UTILITIES_HXX
#define LVCPP_UTILITIES_HXX

#include <cstdint>
#include <iterator>

namespace lv {
  template <typename Iterator>
  using category_of = typename std::iterator_traits<std::remove_cv_t<Iterator>>::iterator_category;

  template <typename Iterator>
  using value_type_of = typename std::iterator_traits<std::remove_cv_t<Iterator>>::value_type;

  template <typename Iterator>
  using difference_type_of = typename std::iterator_traits<std::remove_cv_t<Iterator>>::difference_type;

  template <typename Iterator>
  using pointer_of = typename std::iterator_traits<std::remove_cv_t<Iterator>>::pointer;

  template <typename Iterator>
  using reference_of = typename std::iterator_traits<std::remove_cv_t<Iterator>>::reference;

  namespace detail {
    template <typename Type, typename = std::void_t<>>
    struct is_iterator : std::false_type
    {
    };

    template <typename Type>
    struct is_iterator<Type, std::void_t<
        category_of<Type>,
        value_type_of<Type>,
        difference_type_of<Type>,
        pointer_of<Type>,
        reference_of<Type>
    >> : std::true_type
    {
    };
  }

  template <typename Iterator>
  constexpr static bool const is_iterator_v = detail::is_iterator<Iterator>::value;

  namespace detail {
    template <typename Type>
    class is_iterable
    {
#pragma clang diagnostic push
#pragma ide diagnostic ignored "NotImplementedFunctions"

      template <typename>
      static std::false_type check(...);

      template <typename Iterable>
      static auto check(int) -> decltype(
      std::begin(std::declval<Iterable>()), std::end(std::declval<Iterable>()), std::true_type {}
      );

#pragma clang diagnostic pop

    public:
      constexpr static bool const value = decltype(check<Type>(42))::value;
    };
  }

  template <typename Iterable>
  constexpr static bool const is_iterable_v = detail::is_iterable<Iterable>::value;
}

#endif // LVCPP_UTILITIES_HXX
