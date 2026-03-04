#include "lrnd_base.hpp"


lrnd::lrnd_base::lrnd_base() :
  mod_poly256_(detail::form_mod_poly< 256 >()),
  mod_poly512_(detail::form_mod_poly< 512 >()),
  poly_()
{}


