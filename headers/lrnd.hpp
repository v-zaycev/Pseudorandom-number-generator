#ifndef LRND_HPP
#define LRND_HPP

#include "lrnd_base.hpp"

namespace lrnd
{
  template< RandomNumberType T >
  class lrnd : protected lrnd_base
  {
  public:
    lrnd() :
      lrnd_base()
    {
      lrnd_base::discard< sizeof(T) >(42);
    }
      
    lrnd(lrnd&& other_) = default;
    lrnd(const lrnd& other_) = default;
    explicit lrnd(size_t seed):
      lrnd_base()
    {
      lrnd_base::discard< sizeof(T) >(seed);
    }
    lrnd& operator=(lrnd&& other_) = default;
    lrnd& operator=(const lrnd& other_) = default;
    ~lrnd() = default;

    inline T operator()() noexcept { return lrnd_base::operator()< T >(); }
    void seed(size_t seed) { lrnd_base::discard< sizeof(T) >(seed + 1, lrnd::basic_offset_); }
    void discard(size_t shift) { lrnd_base::discard< sizeof(T) >(shift); }
  };
}
#endif
