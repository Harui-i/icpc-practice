#ifndef HARUILIB_FORMAL_POWER_SERIES_SPARSE_FPS_HPP
#define HARUILIB_FORMAL_POWER_SERIES_SPARSE_FPS_HPP

#include <cassert>
#include <vector>

// forward decl to avoid circular include: formal-power-series.hpp includes this file
template <typename mint>
struct FPS;

// FPSの非ゼロな項を集めたvector<pair<int,mint>>を返す
template <typename mint>
std::vector<std::pair<int, mint>> get_nonzeros(const FPS<mint>& f) {
  std::vector<std::pair<int, mint>> ret;
  for (int i = 0; i < f.size(); i++) {
    if (f[i] != mint(0)) ret.emplace_back(i, f[i]);
  }
  return ret;
}

// ↓--- inverse of sparse fps ---↓
// calculate inverse of f(sparse)
// deg : -1 + ( maximum degree of g )
template <typename mint>
FPS<mint> inv_sparse(const std::vector<std::pair<int, mint>>& f, int deg) {
  assert(deg >= 0);
  for (int i = 0; i < (int)f.size() - 1; i++) assert(f[i].first < f[i + 1].first);
  assert(f[0].first == 0 && f[0].second != mint(0));

  mint f0inv = f[0].second.inv();
  std::vector<mint> g(deg);
  g[0] = f0inv;
  for (int i = 0; i < deg - 1; i++) {
    for (std::pair<int, mint> pim : f) {
      if (i + 1 - pim.first >= 0)
        g[i + 1] -= pim.second * g[i + 1 - pim.first];
      else
        continue;
    }
    g[i + 1] *= f0inv;
  }

  return g;
}

template <typename mint>
FPS<mint> inv_sparse(const FPS<mint>& f, int deg) {
  return inv_sparse(get_nonzeros(f), deg);
}

template <typename mint>
FPS<mint> FPS<mint>::inv_sparse(int deg) const {
  return ::inv_sparse(*this, deg);
}

// ↑--- inverse of sparse fps ----↑

// exp(f)のdeg次未満の部分を求める。
// F := exp(f) = F_0 + F_1 x + F_2 x^2 + ... とする。
// F' = F * f' なので
// F_1 + 2F_2 x + 3F_3 x^3 + ... = f' F.
// 0以上の整数iについて、i次の項に注目すると、
// (i+1) * F_{i+1} = [x^i] (f' * F)
// とわかる。Fは0,1,...,i次までわかってればF_{i+1}もわかるということになる。f'はスパースだからF_{i+1}はたかだかK回の計算で求められる.

template <typename mint>
FPS<mint> exp_sparse(const FPS<mint>& f, int deg) {
  FPS<mint> F(deg);
  F[0] = mint(1);

  std::vector<std::pair<int, mint>> nonzero_fdiff = get_nonzeros(f.diff());

  for (int i = 0; i + 1 < deg; i++) {
    // F[i+1]を求める
    // (i+1) * F_{i+1} = [x^i] (f' * F)

    for (std::pair<int, mint> pim : nonzero_fdiff) {
      int a = pim.first;
      // Fのi-a次の項を足していく
      if (i - a < 0) continue;
      assert(i - a >= 0);
      assert(i + 1 > i - a);
      F[i + 1] += pim.second * F[i - a];
    }
    F[i + 1] /= mint(i + 1);
  }
  return F;
}

template <typename mint>
FPS<mint> FPS<mint>::exp_sparse(int deg) const {
  return ::exp_sparse(*this, deg);
}

template <typename mint>
FPS<mint> log_sparse(const FPS<mint>& f, int deg) {
  FPS<mint> f_inv = inv_sparse(f, deg);
  return multiply_sparse(f_inv, f.diff(), deg).integral().pre(deg);
}

template <typename mint>
FPS<mint> FPS<mint>::log_sparse(int deg) const {
  return ::log_sparse(*this, deg);
}

// g := f ^ k
// g' = k * f^{k-1} * f'
// fg' = k * f^k * f'
// fg' = k * g * f'

template <typename mint>
FPS<mint> pow_sparse(const FPS<mint>& f, long long k, int deg) {
  if (k == 0) {
    FPS ret = {mint(1)};
    ret.resize(deg);
    return ret;
  }

  if (f[0] == mint(0)) {
    int mindeg = 0;
    while (mindeg < deg && f[mindeg] == mint(0)) mindeg++;

    // (x^{mindeg})^k = x^{mindeg * k}
    // mindeg * k >= deg ⇔ k >= floor(deg / mindeg) である。
    // →: 自明 (k >= deg / mindeg >= floor(deg / mindeg) なので)

    // ←について:  h1: k >= floor(deg / mindeg) を仮定して Goal: k >= degを示す。
    // deg = mindeg * q + r (0 <= r < mindeg)と表す。これを使うと
    // h1: k >= q.
    // Goal: k >= mindeg * q + r.

    // mindeg * k > LLINF
    // mindeg > LLINF / k
    constexpr long long INF = 4450000000011100000;
    if (mindeg > INF / k || mindeg * k >= deg) {
      FPS<mint> ret(deg);
      assert(ret[0] == mint(0));
      return ret;
    }
    return pow_sparse(f >> mindeg, k, deg - mindeg * k) << k * mindeg;
  }

  FPS<mint> g(deg);
  assert(f[0] != mint(0));
  g[0] = f[0].pow(k);

  std::vector<std::pair<int, mint>> nonzero_f = get_nonzeros(f);

  for (int i = 0; i + 1 < deg; i++) {
    // g[0], g[1], ..., g[i]が判っている状態で,x^iに注目してg[i+1]を求めにいく。

    // fg' = (f[0] + f[1]x + f[2]x^2 + ... + f[i]x^i)(g[1] + 2g[2]x + 3g[3]x^2 + ... + ig[i]x^{i-1} + (i+1)g[i+1]x^i)
    // (左) kgf' = k(g[0] + g[1]x + g[2]x^2 + ... + g[i]x^i) * (f[1] + 2*f[2]x 3*f[3]x^2 + ... + i*f[i]x^{i-1} +
    // (i+1)*f[i+1]x^i) (右)

    // 左のx^iの係数は f[0](i+1)g[i+1] + f[1]ig[i] + f[2](i-1)g[i-1] + ... + f[i]g[1]
    // 右のx^iの係数は k * ( g[0]*(i+1)f[i+1] +  g[1]if[i] + ... + g[i]*1f[1])

    // f[0](i+1)g[i+1] = k * (g[0]*(i+1)f[i+1] + g[1]if[i] + ... + g[i]*1f[1]) - f[1]ig[i] - f[2](i-1)g[i-1] - ... -
    // f[i]g[1]

    mint sum(0);
    for (std::pair<int, mint> pim : nonzero_f) {
      // f[pim.first]: pim.second
      // 左では 0 <= pim.first <= i
      // 右では 1 <= pim.first <= i+1の部分を見る

      if (0 <= pim.first && pim.first <= i) sum -= pim.second * mint(i + 1 - pim.first) * g[i + 1 - pim.first];
      if (1 <= pim.first && pim.first <= i + 1) sum += mint(k) * g[i + 1 - pim.first] * mint(pim.first) * pim.second;
    }

    // for (int j=0; j<=i; j++) sum += mint(k) * g[j] * mint(i+1-j) * f[i+1-j];
    // for (int j=1; j<=i; j++) sum -= f[j] * mint(i+1-j) * g[i+1-j];

    g[i + 1] = sum / f[0] / mint(i + 1);
  }

  return g;
}

template <typename mint>
FPS<mint> FPS<mint>::pow_sparse(long long k, int deg) const {
  return ::pow_sparse(*this, k, deg);
}

// tabun baggute masu.
template <typename mint>
FPS<mint> multiply_sparse(const FPS<mint>& f, const std::vector<std::pair<int, mint>>& g, int deg = -1) {
  if (deg == -1) deg = f.size() - 1 + g.back().first + 1;

  FPS<mint> ret(deg);
  for (std::pair<int, mint> pim : g) {
    assert(pim.second != 0);
    if (pim.second == 0) continue;

    for (int i = 0; i < f.size(); i++) {
      if (i + pim.first >= ret.size()) continue;
      if (f[i] != mint(0) && pim.second != mint(0)) ret[i + pim.first] += pim.second * f[i];
    }
  }

  return ret;
}

template <typename mint>
FPS<mint> multiply_sparse(const FPS<mint>& f, const FPS<mint>& g, int deg = -1) {
  std::vector<std::pair<int, mint>> vpmi;

  for (int i = 0; i < g.size(); i++)
    if (g[i] != mint(0)) vpmi.emplace_back(i, g[i]);

  return multiply_sparse(f, vpmi, deg);
}

template <typename mint>
FPS<mint> FPS<mint>::mul_sparse(const FPS<mint>& g, int deg) const {
  return multiply_sparse(*this, g, deg);
}

#endif  // HARUILIB_FORMAL_POWER_SERIES_SPARSE_FPS_HPP
