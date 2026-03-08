#include <bit>
#include <bitset>
#include <iostream>
int main()
{
  std::cout << "checked\n\n" << std::endl;

  for (unsigned x{}; x != 010; ++x)
    std::cout << "bit_width( "
    << std::bitset<4>{x} << " ) = "
    << std::bit_width(x) << '\n';
  
  //system("pause");
  return 0;
}