#include "lrnd_base.hpp"
#include <bitset>
#include <array>
#include <iostream>

#include "lrnd_types.hpp"
#include "lrnd_utils.hpp"

using namespace lrnd;

lrnd_base::lrnd_base() :
  poly_{}
{
  this->seed(42);
}

lrnd_base::lrnd_base(size_t seed) :
  poly_{}
{
  this->seed(seed);
}

unsigned int lrnd::lrnd32_opt::max() noexcept
{
  return 0xffffffffu;
}

unsigned int lrnd::lrnd32_opt::min() noexcept
{
  return 0x00000000u;
}

unsigned int lrnd::lrnd32_opt::operator()() noexcept
{
  generated_number_ = 0;
  for (size_t i = 0; i < 32; ++i)
  {
    generated_number_ <<= 1;
    if (poly_[255])
    {
      poly_ ^= mod_poly256_;
      generated_number_ |= 1;
    }
    poly_ <<= 1;
  }
  return generated_number_;
}

unsigned int lrnd::lrnd32_opt::operator()(bool) noexcept
{
  generated_number_ = poly_us_[0];
  generated_number_ <<= 16;
  generated_number_ += poly_us_[1];

  const unsigned short* temp1 = std::addressof((*compressed_mod_poly_us_)[poly_us_[0]][0]);
  const unsigned short* temp2 = std::addressof((*compressed_mod_poly_us_)[poly_us_[1]][0]);

  unsigned int* base = reinterpret_cast<unsigned int*>(poly_us_);
  for (unsigned int* i = base; i != base + 6; ++i)
  {
    *i = *(i + 1);
  }
  poly_us_[12] = poly_us_[14] ^ temp1[0];
  poly_us_[13] = poly_us_[15] ^ temp1[1] ^ temp2[0];
  poly_us_[14] = temp1[2] ^ temp2[1];
  poly_us_[15] = temp2[2];
  return generated_number_;
}

unsigned int lrnd::lrnd32_opt::operator()(char) noexcept
{
  generated_number_ = poly_ull_[0] >> 32;
  unsigned char compressed_nmb = unsigned char(poly_ull_[0] >> 56);
  unsigned long long temp0 = compressed_mod_poly_ull_[compressed_nmb] << 24;
  compressed_nmb = unsigned char((poly_ull_[0] >> 48) & 0xff);
  unsigned long long temp1 = compressed_mod_poly_ull_[compressed_nmb] << 16;
  compressed_nmb = unsigned char((poly_ull_[0] >> 40) & 0xff);
  unsigned long long temp2 = compressed_mod_poly_ull_[compressed_nmb] << 8;
  compressed_nmb = unsigned char((poly_ull_[0] >> 32) & 0xff);
  unsigned long long temp3 = compressed_mod_poly_ull_[compressed_nmb];


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

void lrnd_base::discard(size_t z)
{
  poly512_t poly(this->poly_.to_string());
  for (size_t i = 0; z; ++i)
  {
    if (z & 1)
    {
      poly = mod_mult(mod_poly512_, poly, deg2_[5 + i]);
    }
    z >>= 1;
  }
  this->poly_ = poly256_t(poly.to_string().substr(256, 256));

  return;
}
