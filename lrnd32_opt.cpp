#include "lrnd32_opt.hpp"
#include <bitset>
#include <array>
#include <iostream>

using poly512 = std::bitset< 512 >;
using poly256 = std::bitset< 256 >;

template < size_t N >
std::bitset< N > form_mod_poly() noexcept
{
  static_assert(N >= 256, "Invalid poly size, size must be 256 or greater");
  std::bitset< N > mod_poly{};
  mod_poly[0] = 1;
  mod_poly[3] = 1;
  mod_poly[7] = 1;
  mod_poly[31] = 1;
  mod_poly[255] = 1;
  return mod_poly;
}

void shift_16(std::array< unsigned short, 3 >& to_xor)
{
  to_xor[0] <<= 1;
  to_xor[0] |= (to_xor[1] >> 15);
  to_xor[1] <<= 1;
  to_xor[1] |= (to_xor[2] >> 15);
  to_xor[2] <<= 1;
}
void xor_16(std::array< unsigned short, 3 >& to_xor, std::array< unsigned short, 3 >& other)
{
  to_xor[0] ^= other[0];
  to_xor[1] ^= other[1];
  to_xor[2] ^= other[2];
}

std::array< unsigned short, 3 > form_mod_poly16() noexcept
{
  std::array< unsigned short, 3 > mod_poly{};
  mod_poly[2] = 0x0089; //x^7+x^3+1
  mod_poly[1] = 0x8000; //x^31
  return mod_poly;
}

unsigned long long  form_mod_poly64() noexcept
{
  return (1ull << 0) | (1ull << 3) | (1ull << 7) | (1ull << 31);
}

std::array< std::array< unsigned short, 3 >, 65536 >* compress_mod() noexcept
{
  std::array< unsigned short, 3 >  mod_poly = form_mod_poly16();
  std::array< std::array< unsigned short, 3 >, 65536 >* compressed_poly = new std::array< std::array< unsigned short, 3 >, 65536 >();
  shift_16(mod_poly);
  for (size_t i = 1; i < 65536; i<<=1)
  {
    for (size_t j = i; j < 65536; ++j)
    {
      if (i & j)
      {
        xor_16((*compressed_poly)[j], mod_poly);
      }
    }
    shift_16(mod_poly);
  }
  return compressed_poly;
}

std::array< unsigned long long, 256 >* compress_mod64() noexcept
{
  std::array< unsigned long long, 256 >* compressed_poly = new std::array< unsigned long long, 256 >();
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
    (*compressed_poly)[i] = res;
  }
  return compressed_poly;
}


std::array< poly512, 256 > form_deg2(const poly512& mod_poly) noexcept;
poly512 mod_mult(const poly512& mod_poly, const poly512& poly1, const poly512& poly2) noexcept;

const poly512 zaitsev::lrnd32_opt::mod_poly512_ = form_mod_poly< 512 >();
const poly256 zaitsev::lrnd32_opt::mod_poly256_ = form_mod_poly< 256 >();
const std::array< unsigned short, 3 > zaitsev::lrnd32_opt::mod_poly_us_ = form_mod_poly16();
const unsigned long long zaitsev::lrnd32_opt::mod_poly_ull_ = form_mod_poly64();
const std::array< std::array< unsigned short, 3 >, 65536 >* zaitsev::lrnd32_opt::compressed_mod_poly_us_ = compress_mod();
const std::array< unsigned long long, 256 >* zaitsev::lrnd32_opt::compressed_mod_poly_ull_ = compress_mod64();
const std::array< poly512, 256 > zaitsev::lrnd32_opt::deg2_ = form_deg2(lrnd32_opt::mod_poly512_);

zaitsev::lrnd32_opt::lrnd32_opt():
  poly_{},
  generated_number_{}
{
  this->seed(41);
}

zaitsev::lrnd32_opt::lrnd32_opt(size_t seed):
  poly_{},
  poly_us_{},
  generated_number_{}
{
  this->seed(seed);
}

unsigned int zaitsev::lrnd32_opt::max() noexcept
{
  return 0xffffffffu;
}

unsigned int zaitsev::lrnd32_opt::min() noexcept
{
  return 0x00000000u;
}

unsigned int zaitsev::lrnd32_opt::operator()() noexcept
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

unsigned int zaitsev::lrnd32_opt::operator()(bool) noexcept
{
  generated_number_ = poly_us_[0];
  generated_number_ <<= 16;
  generated_number_ += poly_us_[1];

  const unsigned short* temp1 = std::addressof((*compressed_mod_poly_us_)[poly_us_[0]][0]);
  const unsigned short* temp2 = std::addressof((*compressed_mod_poly_us_)[poly_us_[1]][0]);

  unsigned int* base = reinterpret_cast<unsigned int* >(poly_us_);
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

unsigned int zaitsev::lrnd32_opt::operator()(int) noexcept
{
  generated_number_ = poly_ull_[0] >> 32;
  unsigned char compressed_nmb = unsigned char(poly_ull_[0] >> 56);
  const unsigned long long temp0 =(*compressed_mod_poly_ull_)[compressed_nmb] << 24;
  compressed_nmb = unsigned char((poly_ull_[0] >> 48) & 0xff);
  const unsigned long long temp1 = (*compressed_mod_poly_ull_)[compressed_nmb] << 16;
  compressed_nmb = unsigned char((poly_ull_[0] >> 40) & 0xff);
  const unsigned long long temp2 = (*compressed_mod_poly_ull_)[compressed_nmb] << 8;
  compressed_nmb = unsigned char((poly_ull_[0] >> 32) & 0xff);
  const unsigned long long temp3 = (*compressed_mod_poly_ull_)[compressed_nmb];

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

void zaitsev::lrnd32_opt::seed(size_t seed)
{
  poly512 poly{};
  poly[0] = 1;
  size_t offset = basic_offset_;
  for (size_t i = 0; offset; ++i, offset >>= 1)
  {
    if (offset & 1)
    {
      poly = mod_mult(mod_poly512_, poly, deg2_[i]);
    }
  }

  for (size_t i = 32; seed; ++i)
  {
    if (seed & 1)
    {
      poly = mod_mult(mod_poly512_, poly, deg2_[i]);
    }
    seed >>= 1;
  }

  poly <<= 1;

  this->poly_ = poly256(poly.to_string().substr(256, 256));
  for (size_t i = 0; i < 16; ++i)
  {
    unsigned short temp = 1;
    for (size_t j = 0; j < 16; ++j)
    {
      if (this->poly_[i * 16 + j])
      {
        poly_us_[15 - i] |= temp;
      }
      temp <<= 1;
    }
  }

  for (size_t i = 0; i < 4; ++i)
  {
    poly_ull_[3 - i] = 0;
    unsigned long long temp = 1;
    for (size_t j = 0; j < 64; ++j)
    {
      if (this->poly_[i * 64 + j])
      {
        poly_ull_[3 - i] |= temp;
      }
      temp <<= 1;
    }
  }
  //std::cout << std::hex << (*compressed_mod_poly_us_)[1][2] << std::endl;
  //std::cout << std::hex << (*compressed_mod_poly_ull_)[1] << std::endl;
  return;
}

void zaitsev::lrnd32_opt::discard(size_t z)
{
  poly512 poly(this->poly_.to_string());
  for (size_t i = 0; z; ++i)
  {
    if (z & 1)
    {
      poly = mod_mult(mod_poly512_, poly, deg2_[5 + i]);
    }
    z >>= 1;
  }
  this->poly_ = poly256(poly.to_string().substr(256, 256));

  return;
}
