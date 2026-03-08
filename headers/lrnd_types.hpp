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
  using poly128_t = std::bitset< 128 >;
  using poly256_t = std::bitset< 256 >;
  using poly512_t = std::bitset< 512 >;

  namespace detail
  {
    constexpr u64_t form_mod_poly64() noexcept
    {
      constexpr u64_t one = 1;
      return (one << 0) | (one << 3) | (one << 7) | (one << 31);
    }

    template < size_t N >
    constexpr std::bitset< N > form_mod_poly() noexcept
    {
      static_assert(N >= 256, "Invalid poly size, size must be 256 or greater");
      std::bitset< N > mod_poly;
      mod_poly[0] = 1;
      mod_poly[3] = 1;
      mod_poly[7] = 1;
      mod_poly[31] = 1;
      mod_poly[255] = 1;
      return mod_poly;
    }
  }

  inline constexpr u64_t mod_poly64 = detail::form_mod_poly64();
  inline constexpr poly256_t mod_poly256 = detail::form_mod_poly< 256 >();
  inline constexpr poly512_t mod_poly512 = detail::form_mod_poly< 512 >();

  template<typename T>
  concept RandomNumberType =
    std::unsigned_integral<T> &&
    (sizeof(T) == 1 ||
      sizeof(T) == 2 ||
      sizeof(T) == 4 ||
      sizeof(T) == 8) ||
    std::is_same_v<T, float> ||
    std::is_same_v<T, double>;

  template<typename T, size_t N>
  concept HasSize = (sizeof(T) == N);

}
#endif