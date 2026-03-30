# LRND — Minimalistic Random Number Generator

[![C++23](https://img.shields.io/badge/C%2B%2B-23-blue.svg)](https://isocpp.org/)
[![License](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

Header-only C++23 library for random number generation based on LFSR. Supports 8, 16, 32, 64-bit integers and floating-point numbers in [0, 1).

## 📖 Description

The generator is based on linear feedback shift registers (LFSR) over GF(2^255). 
Key properties:
- Period: 2^255 - 1
- Discard complexity: O(log n)
- Suitable for parallel generation


## ✨ Features

- **Header-only** — just include and use
- **Multiple bit widths** — 8, 16, 32, 64-bit generators
- **Floating-point support** — float and double in [0, 1)
- **Deterministic** — same seed = same sequence
- **Zero dependencies** — only standard library

## 📋 Requirements

- C++23 compatible compiler (GCC 14+, Clang 17+, MSVC 19.40+)

## 🚀 Quick Start

```cpp
#include <lrnd.hpp>

int main() {
    // 32-bit integer generator
    lrnd::lrnd< unsigned int > gen;
    uint32_t r = gen();  // random number in [0, 2^32-1]
    
    // Float generator in [0, 1)
    lrnd::lrnd< float > gen_float;
    float f = gen_float();
    
    // Generator with specific seed
    lrnd::lrnd< unsigned int > gen_seeded(123);
    uint32_t r2 = gen_seeded();
}
```

## 📊 Supported Types

| Type | Range | Description |
|------|-------|-------------|
| `lrnd::u8_t` | 0 – 255 | 8-bit unsigned integer |
| `lrnd::u16_t` | 0 – 65,535 | 16-bit unsigned integer |
| `lrnd::u32_t` | 0 – 4,294,967,295 | 32-bit unsigned integer |
| `lrnd::u64_t` | 0 – 18,446,744,073,709,551,615 | 64-bit unsigned integer |
| `float` | [0, 1) | Single-precision floating point |
| `double` | [0, 1) | Double-precision floating point |

> `lrnd::u8_t`, `lrnd::u16_t`, `lrnd::u32_t`, `lrnd::u64_t` are aliases for standard fixed-width types.  
> Any unsigned integer type with matching size (e.g., `unsigned int` on 32-bit systems) is also accepted.

## 🧪 Testing

Build and run tests with Google Test:

```bash
mkdir build && cd build
cmake .. -DBUILD_TESTS=ON
cmake --build . --config Release
./tests/test_generators
```

## 📝 TODO

- [ ] Add statistical tests (Dieharder, TestU01)
- [ ] Improve the API to better match generators from `std`
- [ ] Improve documentation with examples
- [ ] Add CMake package config
- [ ] Add PyBind wrapper
## 🔗 References

- [Original article](http://www.mathnet.ru/rus/mm2844)
- [Original C implementation](https://lira.imamod.ru/projects/FondProgramm/RndLib/lrnd32_v02/)

## 📄 License

MIT License — see LICENSE file.

Copyright (c) 2026 Vladimir Zaitsev



<!--
# Описание

Репозиторий содержит C++ реализацию  алгоритма генерации последовательностей псевдослучайных чисел, описанной в следующей статье 
www.mathnet.ru/rus/mm2844.

Особенность данного алгоритма состоит в том, что он позволяет генерировать единую последовательность псевдослучайных чисел используя несколько потоков. Такой подход можно реализовать за счёт логарифмической сложности метода `discard()`. 

Автором предлагается версия написанная на C (https://lira.imamod.ru/projects/FondProgramm/RndLib/lrnd32_v02/), но ввиду наличия в ней явных утечек памяти (при наличии нескольких `malloc()` нет ни одиного `free()`) я решил написать свою реализацию на C++. 

# Особенности версий 

Базовая и оптимизированная версия генератора имеют интерфейс аналогичный стандартным генераторам по типу `std::linear_congruential_engine` или `std::mersenne_twister_engine`. В базовой версии не учитываются особенности используемого примитивного полинома, что допускает его модернизацию для использования 
иных полиномов. В версии `lrnd32_opt` особенности конкретного примитивного полинома учтены, что позволяет уменьшить число вычислений на порядок.
--->
