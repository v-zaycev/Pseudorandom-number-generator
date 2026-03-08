#ifndef LRND_TABLE_HPP
#define LRND_TABLE_HPP

#include <array>
#include "lrnd_types.hpp"
#include "lrnd_utils.hpp"

namespace lrnd::table
{
  namespace detail
  {
    constexpr std::array<u64_t, 256> calc_compressed_steps() noexcept
    {
        std::array< u64_t, 256 > compressed_steps;
        for (size_t i = 0; i < 256; ++i)
        {
          u8_t ii = i;
          u64_t res = 0;
          u64_t  mod_poly = lrnd::detail::form_mod_poly64() << 1;
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

    constexpr std::array< poly512_t, 256 > calc_deg2() noexcept
    {
        std::array< poly512_t, 256 > deg2{};

        deg2[0][1] = 1;
        for (size_t i = 1; i < 256; ++i)
        {
          deg2[i] = lrnd::detail::mod_mult(deg2[i - 1], deg2[i - 1]);
        }
        return deg2;
    }
  }
  inline constexpr std::array<u64_t, 256> compressed_steps = detail::calc_compressed_steps();
  inline constexpr std::array<poly512_t, 256> deg2 = detail::calc_deg2();
}
#endif
