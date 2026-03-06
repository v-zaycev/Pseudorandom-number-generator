#ifndef LRND32_OPT
#define LRND32_OPT
#include <bitset>
#include <cstddef>
#include <array>
#include "lrnd_types.hpp"
#include "lrnd_table.hpp"

namespace lrnd
{
  class lrnd32_opt
  {
  public:
    using result_type = unsigned int;

    lrnd32_opt();
    lrnd32_opt(lrnd32_opt&&) = default;
    lrnd32_opt(const lrnd32_opt&) = default;
    explicit lrnd32_opt(size_t seed);
    ~lrnd32_opt() = default;

    static unsigned int max() noexcept;
    static unsigned int min() noexcept;
    result_type operator()() noexcept;
    result_type operator()(bool) noexcept;
    inline result_type operator()(int) noexcept;
    result_type operator()(char) noexcept;
    void seed(size_t seed);
    void discard(size_t seed);
  protected:
    const std::array< u64_t, 256 >& compressed_mod_poly_ull_ = lrnd::table::compressed_steps;
  private:
    using ull = unsigned long long;
    static constexpr size_t basic_offset_ = 183758644ull;
    static const poly512_t mod_poly512_;
    static const poly256_t mod_poly256_;
    static const std::array< unsigned short, 3 > mod_poly_us_;
    static const unsigned long long mod_poly_ull_;
    static const std::array< std::array< unsigned short, 3 >, 65536 >* compressed_mod_poly_us_;
    //static const std::array< ull, 256 >* compressed_mod_poly_ull_;
    static const std::array< poly512_t, 256 > deg2_;
    poly256_t poly_;
    unsigned short poly_us_[16];
    ull poly_ull_[4];
    result_type generated_number_;
  };
}

inline unsigned int lrnd::lrnd32_opt::operator()(int) noexcept
{
  generated_number_ = poly_ull_[0] >> 32;
  u8_t compressed_nmb = u8_t{ poly_ull_[0] >> 56 };
  u64_t temp0 = compressed_mod_poly_ull_[compressed_nmb] << 24;
  compressed_nmb = u8_t{ (poly_ull_[0] >> 48) & 0xff };
  u64_t temp1 = compressed_mod_poly_ull_[compressed_nmb] << 16;
  compressed_nmb = u8_t{ (poly_ull_[0] >> 40) & 0xff };
  u64_t temp2 = compressed_mod_poly_ull_[compressed_nmb] << 8;
  compressed_nmb = u8_t{ (poly_ull_[0] >> 32) & 0xff };
  u64_t temp3 = compressed_mod_poly_ull_[compressed_nmb];


  poly_ull_[0] <<= 32;
  poly_ull_[0] |= poly_ull_[1] >> 32;
  poly_ull_[1] <<= 32;
  poly_ull_[1] |= poly_ull_[2] >> 32;
  poly_ull_[2] <<= 32;
  poly_ull_[2] |= poly_ull_[3] >> 32;
  poly_ull_[3] <<= 32;

  poly_ull_[3] ^= temp0;
  poly_ull_[3] ^= temp1;
  poly_ull_[3] ^= temp2;
  poly_ull_[3] ^= temp3;
  return generated_number_;
}

#endif
