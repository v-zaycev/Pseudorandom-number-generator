#ifndef LRND_UTILS_HPP
#define LRND_UTILS_HPP

#include <bitset>
#include <array>
#include "lrnd_types.hpp"

namespace lrnd
{
  namespace detail 
  {
    template< typename T >
    inline T to_bitset(const std::array<u64_t, 4>& poly)
    {
      T res_poly;

      for (u64_t i : poly)
      {
        res_poly <<= 64;
        res_poly ^= T(i);
      }
      return res_poly;
    }

    //костылирование всех бит по очереди
    inline void to_array(std::array<u64_t, 4>& poly_array, const poly256_t& poly_bitset)
    {
      for (size_t i = 0; i < 4; ++i)
      {
        poly_array[3 - i] = 0;
        u64_t temp = 1;
        for (size_t j = 0; j < 64; ++j)
        {
          if (poly_bitset[i * 64 + j])
          {
            poly_array[3 - i] |= temp;
          }
          temp <<= 1;
        }
      }
    }

    constexpr poly512_t mod_mult(const poly512_t& poly1, const poly512_t& poly2)
    {
      poly512_t res_poly{};
      for (size_t i = 0; i < 256; ++i)
      {
        if (poly1[i])
        {
          res_poly ^= poly2 << i;
        }
      }
      for (size_t i = 511; i > 254; --i)
      {
        if (res_poly[i])
        {
          res_poly ^= lrnd::mod_poly512 << (i - 255);
        }
      }
      return res_poly;
    }
  }
}

#endif 
