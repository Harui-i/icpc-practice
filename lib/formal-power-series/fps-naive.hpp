#ifndef HARUILIB_FORMAL_POWER_SERIES_NAIVE_FPS_HPP
#define HARUILIB_FORMAL_POWER_SERIES_NAIVE_FPS_HPP

#include "formal-power-series/formal-power-series.hpp"

template<typename mint>
std::vector<mint> FPS<mint>::multiply(const std::vector<mint>& a, const std::vector<mint>& b) {
  if (a.size() == 0 || b.size() == 0) return std::vector<mint>();
  vector<mint> ret(a.size() + b.size() - 1);
  for(int i=0; i<int(a.size()); i++) {
    for(int j=0; j<int(b.size()); j++) {
      ret[i+j] += a[i] * b[j];
    }
  }

  return ret;
}

// TODO: ナイーブな筆算のほうが定数倍が(たぶん)良いのでそれにするべき
// とりあえずはNewton法のほうが実装が楽なのでそれでやる
template <typename mint>
void FPS<mint>::next_inv(FPS<mint>& g) const {

  int d = g.size();
  FPS<mint> g_2d = (mint(2) * g  - (*this) * g * g).pre(2*d);
  g = g_2d;
}


template <typename mint>
FPS<mint> FPS<mint>::inv(int deg) const {
  assert(_vec[0] != mint(0));
  if (deg == -1) deg = size();
  FPS g(1);
  g._vec[0] = mint(_vec[0]).inv();

  for (int d = 1; d < deg; d <<= 1) {
    next_inv(g);
  }

  return g.pre(deg);
}

template<typename mint> 
void FPS<mint>::CooleyTukeyNTT998244353([[maybe_unused]] std::vector<mint>& a, [[maybe_unused]] bool is_reverse) const {
  assert(false);
  return;
}
#endif // HARUILIB_FORMAL_POWER_SERIES_NAIVE_FPS_HPP