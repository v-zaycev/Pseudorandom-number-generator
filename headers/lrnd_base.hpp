#ifndef LRND_BASE_HPP
#define LRND_BASE_HPP
#include "lrnd_types.hpp"
#include "lrnd_table.hpp"

namespace lrnd
{
  namespace detail
  {
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
  }

  class lrnd_base
  {
  public:
    lrnd_base();
    lrnd_base(lrnd_base&& other_) = default;
    lrnd_base(const lrnd_base& other_) = default;
    lrnd_base& operator=(lrnd_base&& other_) = default;
    lrnd_base& operator=(const lrnd_base& other_) = default;
    ~lrnd_base();
  private:
    static constexpr size_t basic_offset_ = 183758644ull;
    static constexpr std::array< poly512_t, 256 >& deg2_;
    const poly512_t mod_poly512_;
    const poly256_t mod_poly256_;
    const std::array< u64_t, 256 >& compressed_steps_ = table::compressed_steps;
    std::array< u64_t, 4 > poly_;
  };
}

#endif
