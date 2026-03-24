#include "lrnd_core.hpp"
#include "lrnd_core.hpp"

namespace lrnd
{
  template<>
  class lrnd_core< u8_t >
  {
  public:
    lrnd_core() = delete;
    lrnd_core(lrnd_core< u8_t >&&) = default;
    lrnd_core(const lrnd_core< u8_t >&) = default;
    u8_t next();
    static constexpr u8_t max() noexcept;
    static constexpr u8_t min() noexcept;
    u8_t operator()() noexcept;
    u8_t operator()(bool) noexcept;
    inline u8_t operator()(int) noexcept;
    u8_t operator()(char) noexcept;
    void seed(size_t seed);
    void discard(size_t seed);
  private:
    const std::array< u64_t, 256 >& compressed_mod_poly_ull_ = lrnd::table::compressed_steps;
  };

  template<>
  class lrnd_core< u16_t >
  {
  public:
    lrnd_core() = delete;
    lrnd_core(lrnd_core< u16_t >&&) = default;
    lrnd_core(const lrnd_core< u16_t >&) = default;
    u8_t next();
    static constexpr u8_t max() noexcept;
    static constexpr u8_t min() noexcept;
    u8_t operator()() noexcept;
    u8_t operator()(bool) noexcept;
    inline u8_t operator()(int) noexcept;
    u8_t operator()(char) noexcept;
    void seed(size_t seed);
    void discard(size_t seed);
  private:
    const std::array< u64_t, 256 >& compressed_mod_poly_ull_ = lrnd::table::compressed_steps;
  };

  template<>
  class lrnd_core< u8_t >
  {
  public:
    lrnd_core() = delete;
    lrnd_core(lrnd_core< u8_t >&&) = default;
    lrnd_core(const lrnd_core< u8_t >&) = default;
    u8_t next();
    static constexpr u8_t max() noexcept;
    static constexpr u8_t min() noexcept;
    u8_t operator()() noexcept;
    u8_t operator()(bool) noexcept;
    inline u8_t operator()(int) noexcept;
    u8_t operator()(char) noexcept;
    void seed(size_t seed);
    void discard(size_t seed);
  private:
    const std::array< u64_t, 256 >& compressed_mod_poly_ull_ = lrnd::table::compressed_steps;
  };

  template<>
  class lrnd_core< u8_t >
  {
  public:
    lrnd_core() = delete;
    lrnd_core(lrnd_core< u8_t >&&) = default;
    lrnd_core(const lrnd_core< u8_t >&) = default;
    u8_t next();
    static constexpr u8_t max() noexcept;
    static constexpr u8_t min() noexcept;
    u8_t operator()() noexcept;
    u8_t operator()(bool) noexcept;
    inline u8_t operator()(int) noexcept;
    u8_t operator()(char) noexcept;
    void seed(size_t seed);
    void discard(size_t seed);
  private:
    const std::array< u64_t, 256 >& compressed_mod_poly_ull_ = lrnd::table::compressed_steps;
  };
}