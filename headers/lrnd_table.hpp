#ifndef LRND_TABLE_HPP
#define LRND_TABLE_HPP

#include "lrnd_types.hpp"
#include <array>

namespace lrnd::table
{
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

    constexpr std::array<u64_t, 256> calc_compressed_steps() noexcept
    {
        std::array< u64_t, 256 > compressed_steps;
        for (size_t i = 0; i < 256; ++i)
        {
          u8_t ii = i;
          u64_t res = 0;
          u64_t  mod_poly = form_mod_poly64() << 1;
          while (ii != 0)
          {
            if (ii & 1)
            {
              res ^= mod_poly;
            }
            mod_poly <<= 1;
            ii >>= 1;
          }
          compressed_steps[i] = res;
        }
        return compressed_steps;
    }

    constexpr std::array<poly512_t, 256> calc_deg2(const poly512_t& mod_poly) noexcept
    {
        std::array< poly512_t, 256 > deg2{};

        deg2[0][1] = 1;
        for (size_t i = 1; i < 256; ++i)
        {
          deg2[i] = mod_mult(mod_poly, deg2[i - 1], deg2[i - 1]);
        }
        return deg2;
    }

  }
  inline constexpr u64_t poly64 = detail::form_mod_poly64();
  inline constexpr poly256_t poly256 = detail::form_mod_poly< 256 >();
  inline constexpr poly512_t poly512 = detail::form_mod_poly< 512 >();
  inline constexpr std::array<u64_t, 256> compressed_steps = detail::calc_compressed_steps();
  inline constexpr std::array<poly512_t, 256> deg2 = detail::calc_deg2();
}

#endif
