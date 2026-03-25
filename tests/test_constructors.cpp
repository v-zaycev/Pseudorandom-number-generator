#include <gtest/gtest.h>
#include <lrnd.hpp>

// u8_t

TEST(ConstructorTest8, DefaultConstructor8) 
{
  lrnd::lrnd< lrnd::u8_t > gen1;
  lrnd::lrnd< lrnd::u8_t > gen2;

  EXPECT_EQ(gen1(), gen2());
  EXPECT_EQ(gen1(), gen2());
}

TEST(ConstructorTest8, SeedConstructor8) {
  lrnd::lrnd< lrnd::u8_t > gen1(123);
  lrnd::lrnd< lrnd::u8_t > gen2(123);
  lrnd::lrnd< lrnd::u8_t > gen3(456);

  EXPECT_EQ(gen1(), gen2());
  EXPECT_NE(gen1(), gen3());
}

TEST(ConstructorTest8, CopyConstructor8) {
  lrnd::lrnd<lrnd::u8_t> gen1;
  lrnd::lrnd<lrnd::u8_t> gen2(gen1);
  
  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest8, MoveConstructor8) {
  lrnd::lrnd<lrnd::u8_t> gen1;
  lrnd::lrnd<lrnd::u8_t> gen2(gen1);
  lrnd::lrnd< lrnd::u8_t > gen3(std::move(gen1));

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();

  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest8, CopyAssignment8) {
  lrnd::lrnd< lrnd::u8_t > gen1, gen2;
  gen2 = gen1;

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest8, MoveAssignment8) {
  lrnd::lrnd< lrnd::u8_t > gen1;
  lrnd::lrnd< lrnd::u8_t > gen2(gen1);
  lrnd::lrnd< lrnd::u8_t > gen3;
  gen2 = std::move(gen1);

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();
  EXPECT_EQ(val3, val4);
}

// u16_t

TEST(ConstructorTest16, DefaultConstructor16)
{
  lrnd::lrnd< lrnd::u16_t > gen1;
  lrnd::lrnd< lrnd::u16_t > gen2;

  EXPECT_EQ(gen1(), gen2());
  EXPECT_EQ(gen1(), gen2());
}

TEST(ConstructorTest16, SeedConstructor16) {
  lrnd::lrnd< lrnd::u16_t > gen1(123);
  lrnd::lrnd< lrnd::u16_t > gen2(123);
  lrnd::lrnd< lrnd::u16_t > gen3(456);

  EXPECT_EQ(gen1(), gen2());
  EXPECT_NE(gen1(), gen3());
}

TEST(ConstructorTest16, CopyConstructor16) {
  lrnd::lrnd<lrnd::u16_t> gen1;
  lrnd::lrnd<lrnd::u16_t> gen2(gen1);

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest16, MoveConstructor16) {
  lrnd::lrnd<lrnd::u16_t> gen1;
  lrnd::lrnd<lrnd::u16_t> gen2(gen1);
  lrnd::lrnd< lrnd::u16_t > gen3(std::move(gen1));

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();

  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest16, CopyAssignment16) {
  lrnd::lrnd< lrnd::u16_t > gen1, gen2;
  gen2 = gen1;

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest16, MoveAssignment16) {
  lrnd::lrnd< lrnd::u16_t > gen1;
  lrnd::lrnd< lrnd::u16_t > gen2(gen1);
  lrnd::lrnd< lrnd::u16_t > gen3;
  gen2 = std::move(gen1);

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();
  EXPECT_EQ(val3, val4);
}

// u32_t

TEST(ConstructorTest32, DefaultConstructor32)
{
  lrnd::lrnd< lrnd::u32_t > gen1;
  lrnd::lrnd< lrnd::u32_t > gen2;

  EXPECT_EQ(gen1(), gen2());
  EXPECT_EQ(gen1(), gen2());
}

TEST(ConstructorTest32, SeedConstructor) {
  lrnd::lrnd< lrnd::u32_t > gen1(123);
  lrnd::lrnd< lrnd::u32_t > gen2(123);
  lrnd::lrnd< lrnd::u32_t > gen3(456);

  EXPECT_EQ(gen1(), gen2());
  EXPECT_NE(gen1(), gen3());
}

TEST(ConstructorTest32, CopyConstructor32) {
  lrnd::lrnd<lrnd::u32_t> gen1;
  lrnd::lrnd<lrnd::u32_t> gen2(gen1);

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest32, MoveConstructor32) {
  lrnd::lrnd<lrnd::u32_t> gen1;
  lrnd::lrnd<lrnd::u32_t> gen2(gen1);
  lrnd::lrnd< lrnd::u32_t > gen3(std::move(gen1));

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();

  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest32, CopyAssignment32) {
  lrnd::lrnd< lrnd::u32_t > gen1, gen2;
  gen2 = gen1;

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest32, MoveAssignment32) {
  lrnd::lrnd< lrnd::u32_t > gen1;
  lrnd::lrnd< lrnd::u32_t > gen2(gen1);
  lrnd::lrnd< lrnd::u32_t > gen3;
  gen2 = std::move(gen1);

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();
  EXPECT_EQ(val3, val4);
}

// u64_t

TEST(ConstructorTest64, DefaultConstructor64)
{
  lrnd::lrnd< lrnd::u64_t > gen1;
  lrnd::lrnd< lrnd::u64_t > gen2;

  EXPECT_EQ(gen1(), gen2());
  EXPECT_EQ(gen1(), gen2());
}

TEST(ConstructorTest64, SeedConstructor64) {
  lrnd::lrnd< lrnd::u64_t > gen1(123);
  lrnd::lrnd< lrnd::u64_t > gen2(123);
  lrnd::lrnd< lrnd::u64_t > gen3(456);

  EXPECT_EQ(gen1(), gen2());
  EXPECT_NE(gen1(), gen3());
}

TEST(ConstructorTest64, CopyConstructor64) {
  lrnd::lrnd<lrnd::u64_t> gen1;
  lrnd::lrnd<lrnd::u64_t> gen2(gen1);

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest64, MoveConstructor64) {
  lrnd::lrnd<lrnd::u64_t> gen1;
  lrnd::lrnd<lrnd::u64_t> gen2(gen1);
  lrnd::lrnd< lrnd::u64_t > gen3(std::move(gen1));

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();

  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest64, CopyAssignment64) {
  lrnd::lrnd< lrnd::u64_t > gen1, gen2;
  gen2 = gen1;

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTest64, MoveAssignment64) {
  lrnd::lrnd< lrnd::u64_t > gen1;
  lrnd::lrnd< lrnd::u64_t > gen2(gen1);
  lrnd::lrnd< lrnd::u64_t > gen3;
  gen2 = std::move(gen1);

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();
  EXPECT_EQ(val3, val4);
}


// float 

TEST(ConstructorTestF, DefaultConstructorF)
{
  lrnd::lrnd< float > gen1;
  lrnd::lrnd< float > gen2;

  EXPECT_EQ(gen1(), gen2());
  EXPECT_EQ(gen1(), gen2());
}

TEST(ConstructorTestF, SeedConstructorF) {
  lrnd::lrnd< float > gen1(123);
  lrnd::lrnd< float > gen2(123);
  lrnd::lrnd< float > gen3(456);

  EXPECT_EQ(gen1(), gen2());
  EXPECT_NE(gen1(), gen3());
}

TEST(ConstructorTestF, CopyConstructorF) {
  lrnd::lrnd<float> gen1;
  lrnd::lrnd<float> gen2(gen1);

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTestF, MoveConstructorF) {
  lrnd::lrnd<float> gen1;
  lrnd::lrnd<float> gen2(gen1);
  lrnd::lrnd< float > gen3(std::move(gen1));

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();

  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTestF, CopyAssignmentF) {
  lrnd::lrnd< float > gen1, gen2;
  gen2 = gen1;

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTestF, MoveAssignmentF) {
  lrnd::lrnd< float > gen1;
  lrnd::lrnd< float > gen2(gen1);
  lrnd::lrnd< float > gen3;
  gen2 = std::move(gen1);

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();
  EXPECT_EQ(val3, val4);
}

// double

TEST(ConstructorTestD, DefaultConstructorD)
{
  lrnd::lrnd< double > gen1;
  lrnd::lrnd< double > gen2;

  EXPECT_EQ(gen1(), gen2());
  EXPECT_EQ(gen1(), gen2());
}

TEST(ConstructorTestD, SeedConstructorD) {
  lrnd::lrnd< double > gen1(123);
  lrnd::lrnd< double > gen2(123);
  lrnd::lrnd< double > gen3(456);

  EXPECT_EQ(gen1(), gen2());
  EXPECT_NE(gen1(), gen3());
}

TEST(ConstructorTestD, CopyConstructorD) {
  lrnd::lrnd<double> gen1;
  lrnd::lrnd<double> gen2(gen1);

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTestD, MoveConstructorD) {
  lrnd::lrnd<double> gen1;
  lrnd::lrnd<double> gen2(gen1);
  lrnd::lrnd< double > gen3(std::move(gen1));

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();

  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTestD, CopyAssignmentD) {
  lrnd::lrnd< double > gen1, gen2;
  gen2 = gen1;

  auto val1 = gen1();
  auto val2 = gen2();
  EXPECT_EQ(val1, val2);

  auto val3 = gen1();
  auto val4 = gen2();
  EXPECT_EQ(val3, val4);
}

TEST(ConstructorTestD, MoveAssignmentD) {
  lrnd::lrnd< double > gen1;
  lrnd::lrnd< double > gen2(gen1);
  lrnd::lrnd< double > gen3;
  gen2 = std::move(gen1);

  auto val1 = gen2();
  auto val2 = gen3();
  EXPECT_EQ(val1, val2);

  auto val3 = gen2();
  auto val4 = gen3();
  EXPECT_EQ(val3, val4);
}

