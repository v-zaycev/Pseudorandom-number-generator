#include <bit>
#include <bitset>
#include <iostream>
#include "lrnd.hpp"

int main()
{
  std::cout << "checked\n\n" << std::endl;

  //for (unsigned x{}; x != 010; ++x)
  //  std::cout << "bit_width( "
  //  << std::bitset<4>{x} << " ) = "
  //  << std::bit_width(x) << '\n';
  //

  lrnd::lrnd< lrnd::u16_t > gen8(10000000);
  lrnd::lrnd< uint16_t > gen16(10000000);
  lrnd::lrnd< unsigned short > gen32(10000000);
  lrnd::lrnd< unsigned short > gen64(10000000);
  for (size_t i = 0; i < 20; ++i)
  {
    lrnd::u64_t res{};
    std::cout << i << " ";
    for (int i = 0; i < 2; ++i)
    {
      res <<= 16;
      res ^= gen8();
    }
    std::cout << res << " ";
    res = 0;
    for (int i = 0; i < 2; ++i)
    {
      res <<= 16;
      res ^= gen16();
    }
    std::cout << res << " ";
    res = 0;
    for (int i = 0; i < 2; ++i)
    {
      res <<= 16;
      res ^= gen32();
    }
    std::cout << res << " \n";
    //std::cout << gen64() << " \n";
  }

  /*std::cout << "\n\n";
  lrnd::lrnd< uint32_t > gen2(0);
  gen2.discard(7);
  for (size_t i = 0; i < 100'000'000; ++i)
    std::cout << i << " " << gen2() << std::endl;*/
  //system("pause");
  return 0;
}
