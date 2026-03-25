// tests/test_discard.cpp
#include <gtest/gtest.h>
#include <tuple>
#include "lrnd.hpp"

// ==================== Параметризованные тесты ====================

class DiscardTest : public ::testing::TestWithParam<std::tuple<size_t, size_t>> {
protected:
  size_t GetSeed() const { return std::get<0>(GetParam()); }
  size_t GetDiscardN() const { return std::get<1>(GetParam()); }
};

INSTANTIATE_TEST_SUITE_P(
  DiscardValues,
  DiscardTest,
  ::testing::Combine(
    ::testing::Values(0, 1, 42, 12345),     // seed
    ::testing::Values(0, 1, 2, 3, 7, 8, 15, 16, 32, 64, 100, 128, 256)  // discard_n
  )
);

TEST_P(DiscardTest, DiscardEqualsManualSkip) 
{
  size_t seed = GetSeed();
  size_t discard_n = GetDiscardN();

  lrnd::lrnd<lrnd::u32_t> gen_discard(seed);
  gen_discard.discard(discard_n);

  lrnd::lrnd<lrnd::u32_t> gen_skip(seed);
  for (size_t i = 0; i < discard_n; ++i) 
  {
    gen_skip();
  }

  for (int i = 0; i < 100; ++i) 
  {
    EXPECT_EQ(gen_discard(), gen_skip())
      << "seed = " << seed << ", n = " << discard_n  << ", iteration = " << i;
  }
}

TEST(DiscardTest, DiscardZeroDoesNothing) {
  lrnd::lrnd<lrnd::u32_t> gen1(42);
  lrnd::lrnd<lrnd::u32_t> gen2(42);

  gen1.discard(0);

  for (int i = 0; i < 100; ++i) 
  {
    EXPECT_EQ(gen1(), gen2()) << "iteration " << i;
  }
}


TEST(DiscardTest, MultipleDiscardSum) {
  lrnd::lrnd<lrnd::u32_t> gen1(42);
  lrnd::lrnd<lrnd::u32_t> gen2(42);

  gen1.discard(10);
  gen1.discard(20);
  gen2.discard(30);

  for (int i = 0; i < 100; ++i) {
    EXPECT_EQ(gen1(), gen2()) << "iteration " << i;
  }
}


TEST(DiscardTest, AllTypesSupportDiscard) {
  std::vector<size_t> seeds = { 0, 1, 42, 12345 };
  std::vector<size_t> discards = { 0, 1, 8, 16, 32, 64, 100 };

  for (auto seed : seeds) {
    for (auto n : discards) {
      // u8_t
      lrnd::lrnd<lrnd::u8_t> gen8(seed);
      EXPECT_NO_THROW(gen8.discard(n));

      // u16_t
      lrnd::lrnd<lrnd::u16_t> gen16(seed);
      EXPECT_NO_THROW(gen16.discard(n));

      // u32_t
      lrnd::lrnd<lrnd::u32_t> gen32(seed);
      EXPECT_NO_THROW(gen32.discard(n));

      // u64_t
      lrnd::lrnd<lrnd::u64_t> gen64(seed);
      EXPECT_NO_THROW(gen64.discard(n));
    }
  }
}


TEST(DiscardTest, SeedAfterDiscard) {
  lrnd::lrnd<lrnd::u32_t> gen(42);
  gen.discard(50);
  auto val1 = gen();

  lrnd::lrnd<lrnd::u32_t> gen_new(42);
  gen_new.discard(50);
  auto val2 = gen_new();

  EXPECT_EQ(val1, val2);

  gen.seed(123);
  gen_new.seed(123);
  auto val3 = gen();
  auto val4 = gen_new();

  EXPECT_EQ(val3, val4);
}