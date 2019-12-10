# Less Verbose C++ (lvcpp)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

This is a header only library providing lazily evaluated
functional algorithms for C++.

The basis is the `lv::sequence<Iterator>` class, which represents a pair of iterators.
It provides a `collect<Collection>()` member function,
supporting any target type supporting construction from a pair of iterators.
Sequences are usually created with the `lv::sequence_of()` function template.

## Basic Usage

```cpp
#include <lv/cpp.hxx>

// initializer_list is supported
auto const seq = lv::sequence_of({1, 2, 3, 4});

// so are C style arrays
char const text[] = { 'h', 'e', 'l', 'l', 'o' };
auto const str = lv::sequence_of(text).collect<std::string>();

// optionally
using namespace lv;

// sequences can be created from mostly any kind of container supporting std::begin and std::end
// although sequence_of will use std::cbegin and std::cend as we don't want to modify inputs.
auto const seq = sequence_of("Hello world!"s);
auto const seq = sequence_of(std::vector { 13.37, 3.14159 });

// collecting can be done via the aforementioned collect function
// or via the collector:
auto const numbers = sequence_of({1, 2, 3}) << collect<std::vector<int>>();
// the collector also supports return type deduction:
std::string str = sequence_of({'f', 'o', 'o'}) << collect(); 
```

## Documentation

This README is only supposed to give a short overview.
For actual documentation read the tests ;-)

## Extensibility

As existing classes cannot easily be extended in C++ I make use of operator overloading.
Each of the supported algorithms is connected with the sequence via overloading the `operator <<`.
The results are either another sequence containing a smart iterator implementing the actual job,
or a single return value (might be a container) for aggregations.

## Third Party

This library has no dependencies, but should be compatible with any third party containers employing iterators.

The tests use [Catch2](https://github.com/catchorg/Catch2) provided under the **Boost Software License 1.0**.
