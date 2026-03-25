#include <iostream>
#include "lrnd.hpp"

int main()
{
  
  lrnd::lrnd< unsigned int > gen1(42);
  lrnd::lrnd< lrnd::u32_t > gen2(42);

  gen1.discard(20);
  for (size_t i = 0; i < 10; ++i)
    std::cout << i + 20 << " " << gen1() << std::endl;

  std::cout << "\n\n";

  for (size_t i = 0; i < 30; ++i)
    std::cout << i << " " << gen2() << std::endl;
  
  return 0;
}
