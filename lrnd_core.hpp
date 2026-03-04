#ifndef LRND_CORE_HPP
#define LRND_CORE_HPP

#include "lrnd_types.hpp"
#include "lrnd_table.hpp"
#include "lrnd_base.hpp"
#include <array>

namespace lrnd
{
  template< typename T >
  class lrnd_core : public lrnd_base
  {
  public:
    lrnd_core() = delete;
    T next() = delete;
  private:
    const std::array< u64_t, 256 >& compressed_mod_poly_ull_ = lrnd::table::compressed_steps;
  };
}


#endif // !LRND_CORE_HPP

