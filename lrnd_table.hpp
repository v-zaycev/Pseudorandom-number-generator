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

    constexpr std::array<u64_t, 256> calc_compressed_steps() noexcept
    {
        std::array< u64_t, 256 > compressed_steps;
        for (size_t i = 0; i < 256; ++i)
        {
          unsigned char ii = i;
          unsigned long long res = 0;
          unsigned long long  mod_poly = form_mod_poly64() << 1;
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
  }

  inline constexpr std::array<u64_t, 256> compressed_steps = detail::calc_compressed_steps();
}

#endif
