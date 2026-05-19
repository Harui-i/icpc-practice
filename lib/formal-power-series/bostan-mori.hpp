#include <cassert>
#include <vector>

#include "formal-power-series/formal-power-series.hpp"

template <typename mint>
FPS<mint> fps_even(const FPS<mint>& f) {
  std::vector<mint> ret;
  ret.reserve((f.size() + 1) / 2);
  for (int i = 0; i < f.size(); i += 2) ret.push_back(f[i]);
  return FPS<mint>(ret);
}

template <typename mint>
FPS<mint> fps_odd(const FPS<mint>& f) {
  std::vector<mint> ret;
  ret.reserve(f.size() / 2);
  for (int i = 1; i < f.size(); i += 2) ret.push_back(f[i]);
  return FPS<mint>(ret);
}

// P(x) / Q(x) の x^N の係数を求める
template <typename mint>
mint BostanMori(FPS<mint> P, FPS<mint> Q, unsigned long long N) {
  assert(Q.size() > 0 && Q[0] != mint(0));
  while (N > 0) {
    FPS<mint> Q_neg = Q;
  for (int i = 1; i < Q_neg.size(); i += 2) Q_neg[i] = -Q_neg[i];

    FPS<mint> P2 = P * Q_neg;
    FPS<mint> Q2 = Q * Q_neg;

    if (N & 1) {
      P = fps_odd(P2);
    } else {
      P = fps_even(P2);
    }
    Q = fps_even(Q2);
    N >>= 1;
  }
  assert(P.size() > 0);
  return P[0] / Q[0];
}

// given linear recurrence sequence a_{n+K}= c_1 a_{n+K-1} + c_2 a_{n+k-2} + \dots + c_{K-1} a_{n+1} + c_K a_n
// a_0, a_1, \dots, a_{K-1} are given
// calculate a_N (N-th term of linear recurrence sequence) time complexity is O(K log K log N) (when NNT is used), O(K^2 log N) (when naive convolution is used).
template <typename mint>
mint BostanMori(const std::vector<mint>& a, const std::vector<mint>& c, unsigned long long N) {
  if (N < a.size()) return a[N];
  assert(a.size() == c.size());
  int K = c.size();

  FPS<mint> Q(K + 1);
  Q[0] = mint(1);
  for (int i = 0; i < K; i++) Q[i + 1] = -c[i];

  FPS<mint> P(K);
  for (int i = 0; i < K; i++) {
    mint s = a[i];
    for (int j = 1; j <= i; j++) s -= c[j - 1] * a[i - j];
    P[i] = s;
  }

  return BostanMori(P, Q, N);
}
