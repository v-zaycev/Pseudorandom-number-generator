#ifndef LRND_TYPES_HPP
#define LRND_TYPES_HPP
#include <concepts>
#include <type_traits>
#include <bitset>
#include <cstdint>

namespace lrnd
{
  using u8_t = std::uint8_t;
  using u16_t = std::uint16_t;
  using u32_t = std::uint32_t;
  using u64_t = std::uint64_t;
  using poly512_t = std::bitset< 512 >;
  using poly256_t = std::bitset< 256 >;


  template<typename T>
  concept RandomNumberType =
    std::unsigned_integral<T> &&
    (sizeof(T) == 1 ||
      sizeof(T) == 2 ||
      sizeof(T) == 4 ||
      sizeof(T) == 8) ||
    std::is_same_v<T, float> ||
    std::is_same_v<T, double>;
}
#endif