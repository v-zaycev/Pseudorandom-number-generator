// tests/test_consistency.cpp
#include <gtest/gtest.h>
#include "lrnd.hpp"

class ConsistencyTest : public ::testing::TestWithParam<uint64_t> {};

TEST_P(ConsistencyTest, AllGeneratorsConsistent) 
{
  uint64_t seed = GetParam();

  lrnd::lrnd<lrnd::u8_t> gen8(8 * seed);
  lrnd::lrnd<lrnd::u16_t> gen16(4 * seed);
  lrnd::lrnd<lrnd::u32_t> gen32(2 * seed);
  lrnd::lrnd<lrnd::u64_t> gen64(seed);

  for (size_t i = 0; i < 100; ++i) {

    lrnd::u64_t val8 = 0, val16 = 0, val32 = 0, val64 = 0;

    for (size_t j = 0; j < 8; ++j)
    {
      val8 <<= 8;
      val8 ^= gen8();
    }

    for (size_t j = 0; j < 4; ++j)
    {
      val16 <<= 16;
      val16 ^= gen16();
    }

    for (size_t j = 0; j < 2; ++j)
    {
      val32 <<= 32;
      val32 ^= gen32();
    }

    val64 = gen64();


    EXPECT_EQ(val8, val16)
      << "8-16 mismatch at iteration " << i;

    EXPECT_EQ(val8, val32)
      << "8-32 mismatch at iteration " << i;

    EXPECT_EQ(val8, val64)
      << "8-64 mismatch at iteration " << i;
  }
}

INSTANTIATE_TEST_SUITE_P(
  Seeds,
  ConsistencyTest,
  ::testing::Values(
    0, 1, 32, 42, 12345, 67890,
    99999, 123456789, 0xFFFFFFFF,
    0x123456789ABCDEFULL
  )
);