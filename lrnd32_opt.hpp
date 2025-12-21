#ifndef LRND32_OPT
#define LRND32_OPT
#include <bitset>
#include <cstddef>
#include <emmintrin.h>
#include <immintrin.h>

namespace zaitsev
{
  using poly512 = std::bitset< 512 >;
  using poly256 = std::bitset< 256 >;

  class lrnd32_opt
  {
  public:
    using result_type = unsigned int;

    lrnd32_opt();
    lrnd32_opt(lrnd32_opt&&) = default;
    lrnd32_opt(const lrnd32_opt&) = default;
    explicit lrnd32_opt(size_t seed);
    ~lrnd32_opt() = default;

    static unsigned int max() noexcept;
    static unsigned int min() noexcept;
    result_type operator()() noexcept;
    result_type operator()(bool) noexcept;
    void seed(size_t seed);
    void discard(size_t seed);

  private:
    static constexpr size_t basic_offset_ = 183758644ull;
    static const poly512 mod_poly512_;
    static const poly256 mod_poly256_;
    static const std::array< unsigned short, 3 > mod_poly_us_;
    static const std::array< std::array< unsigned short, 3 >, 65536 >* compressed_mod_poly_us_;
    static const std::array< poly512, 256 > deg2_;
    poly256 poly_;
    unsigned short poly_us_[16];
    result_type generated_number_;
  };
}
#endif
