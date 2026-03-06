#ifndef LRND_BASE_HPP
#define LRND_BASE_HPP
#include "lrnd_types.hpp"
#include "lrnd_table.hpp"

namespace lrnd
{
  class lrnd_base
  {
  public:
    lrnd_base();
    lrnd_base(lrnd_base&& other_) = default;
    lrnd_base(const lrnd_base& other_) = default;
    lrnd_base& operator=(lrnd_base&& other_) = default;
    lrnd_base& operator=(const lrnd_base& other_) = default;
    ~lrnd_base() = default;
    
    static unsigned int max() noexcept;
    static unsigned int min() noexcept;
    template< typename T >
    inline T operator()() noexcept;
    void seed(size_t seed);
    template< HasSize  T >
    void discard(size_t seed);
  private:
    using basic_offset_ = 183758644ull;
    static constexpr std::array< poly512_t, 256 >& deg2_;
    const poly512_t mod_poly512_;
    const poly256_t mod_poly256_;
    const std::array< u64_t, 256 >& compressed_steps_ = table::compressed_steps;
    std::array< u64_t, 4 > poly_;
  };

  template<>
  inline void lrnd_base::discard< 1 >(size_t seed)
  {}

  template<>
  inline void lrnd_base::discard< 2 >(size_t seed)
  {
  }

  template<>
  inline void lrnd_base::discard< 4 >(size_t seed)
  {}

  template<>
  inline void lrnd_base::discard< 8 >(size_t seed)
  {}
}



#endif
