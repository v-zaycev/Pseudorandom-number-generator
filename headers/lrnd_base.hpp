#ifndef LRND_BASE_HPP
#define LRND_BASE_HPP
#include <bit>
#include "lrnd_types.hpp"
#include "lrnd_table.hpp"
#include "lrnd_utils.hpp"

namespace lrnd
{
  class lrnd_base
  {
  public:
    lrnd_base();
    lrnd_base(lrnd_base&& other_) = default;
    lrnd_base(const lrnd_base& other_) = default;
    explicit lrnd_base(size_t seed);
    lrnd_base& operator=(lrnd_base&& other_) = default;
    lrnd_base& operator=(const lrnd_base& other_) = default;
    ~lrnd_base() = default;
    
    //static unsigned int max() noexcept;
    //static unsigned int min() noexcept;
    template< typename T >
    inline T operator()() noexcept;
    template< size_t  N >
    void discard(size_t shift, size_t basic_offset = 1);
  private:
    static constexpr size_t basic_offset_ = 183758644ull;
    std::array< u64_t, 4 > poly_; 
  };

  template<>
  inline u8_t lrnd_base::operator()< u8_t >()
  {
    u8_t generated_number_ = poly_[0] >> 56;
    u8_t compressed_nmb = u8_t{ poly_[0] >> 56 };
    u64_t temp = table::compressed_steps[compressed_nmb] << 24;

    poly_[0] <<= 32;
    poly_[0] |= poly_[1] >> 32;
    poly_[1] <<= 32;
    poly_[1] |= poly_[2] >> 32;
    poly_[2] <<= 32;
    poly_[2] |= poly_[3] >> 32;
    poly_[3] <<= 32;

    poly_[3] ^= temp;
    return generated_number_;
  }

  template<>
  inline u16_t lrnd_base::operator()< u16_t >()
  {
    u16_t generated_number_ = poly_[0] >> 48;
    u8_t compressed_nmb = u8_t{ poly_[0] >> 56 };
    u64_t temp0 = table::compressed_steps[compressed_nmb] << 24;
    compressed_nmb = u8_t{ (poly_[0] >> 48) & 0xff };
    u64_t temp1 = table::compressed_steps[compressed_nmb] << 16;

    poly_[0] <<= 8;
    poly_[0] |= poly_[1] >> 56;
    poly_[1] <<= 8;
    poly_[1] |= poly_[2] >> 56;
    poly_[2] <<= 8;
    poly_[2] |= poly_[3] >> 56;
    poly_[3] <<= 8;

    poly_[3] ^= temp0;
    poly_[3] ^= temp1;
    return generated_number_;
  }

  template<>
  inline u32_t lrnd_base::operator()< u32_t >()
  {
    u32_t generated_number_ = poly_[0] >> 32;
    u8_t compressed_nmb = u8_t{ poly_[0] >> 56 };
    u64_t temp0 = table::compressed_steps[compressed_nmb] << 24;
    compressed_nmb = u8_t{ (poly_[0] >> 48) & 0xff };
    u64_t temp1 = table::compressed_steps[compressed_nmb] << 16;
    compressed_nmb = u8_t{ (poly_[0] >> 40) & 0xff };
    u64_t temp2 = table::compressed_steps[compressed_nmb] << 8;
    compressed_nmb = u8_t{ (poly_[0] >> 32) & 0xff };
    u64_t temp3 = table::compressed_steps[compressed_nmb];


    poly_[0] <<= 32;
    poly_[0] |= poly_[1] >> 32;
    poly_[1] <<= 32;
    poly_[1] |= poly_[2] >> 32;
    poly_[2] <<= 32;
    poly_[2] |= poly_[3] >> 32;
    poly_[3] <<= 32;

    poly_[3] ^= temp0;
    poly_[3] ^= temp1;
    poly_[3] ^= temp2;
    poly_[3] ^= temp3;
    return generated_number_;
  }

  template<>
  inline u64_t lrnd_base::operator()< u64_t >()
  {
    u64_t generated_number_ = poly_[0];
    u8_t compressed_nmb = u8_t{ poly_[0] >> 56 };
    u64_t temp0 = table::compressed_steps[compressed_nmb] << 24;
    compressed_nmb = u8_t{ (poly_[0] >> 48) & 0xff };
    u64_t temp1 = table::compressed_steps[compressed_nmb] << 16;
    compressed_nmb = u8_t{ (poly_[0] >> 40) & 0xff };
    u64_t temp2 = table::compressed_steps[compressed_nmb] << 8;
    compressed_nmb = u8_t{ (poly_[0] >> 32) & 0xff };
    u64_t temp3 = table::compressed_steps[compressed_nmb];
    compressed_nmb = u8_t{ (poly_[0] >> 24) & 0xff };
    u64_t temp4 = table::compressed_steps[compressed_nmb] << 16;
    compressed_nmb = u8_t{ (poly_[0] >> 16) & 0xff };
    u64_t temp5 = table::compressed_steps[compressed_nmb] << 8;
    compressed_nmb = u8_t{ (poly_[0] >> 8) & 0xff };
    u64_t temp6 = table::compressed_steps[compressed_nmb];
    compressed_nmb = u8_t{ poly_[0] & 0xff };
    u64_t temp7 = table::compressed_steps[compressed_nmb] << 16;


    poly_[0] = poly_[1];
    poly_[1] = poly_[2];
    poly_[2] = poly_[3];
    poly_[3] = 0;

    poly_[3] ^= temp0;
    poly_[3] ^= temp1;
    poly_[3] ^= temp2;
    poly_[3] ^= temp3;
    return generated_number_;
  }

  template<>
  inline float lrnd_base::operator()< float >()
  {
    u32_t rnd_nmb = this->operator()< u32_t >();
  }

  template<>
  inline double lrnd_base::operator()< double >()
  {
    u64_t rnd_nmb = this->operator() < u64_t > ();
  }

  template<size_t N>
  void lrnd_base::discard(size_t shift, size_t basic_offset)
  {
    size_t item_shift = std::bit_width(N * 8) - 1;
    poly512_t res_poly;
    res_poly[0] = 1;
    poly256_t offset = poly256_t(shift) << item_shift;
    for (size_t j = 0; basic_offset != 0; ++j, basic_offset >>= 1)
    {
      if (basic_offset[0])
      {
        poly512_t tmp_poly;
        tmp_poly[0] = 1;
        poly256_t tmp_offset = offset << j;
          for (size_t i = 0; offset.any(); ++i, offset >>= 1)
          {
            if (offset[0])
            {
              tmp_poly = detail::mod_mult(res_poly, table::deg2[i]);
            }
          }
          res_poly = detail::mod_mult(res_poly, tmp_poly);
      }
    }
    res_poly <<= 1; //???????????

    detail::to_array(this->poly_, poly256_t(res_poly.to_string().substr(256, 256)));
    return;
  }
}

#endif
