#ifndef HARUILIB_CONVOLUTION_DIVISOR_ZETA_MOEBIUS_TRANSFORM_HPP
#define HARUILIB_CONVOLUTION_DIVISOR_ZETA_MOEBIUS_TRANSFORM_HPP

#include <vector>
#include <map>

namespace divisor {
  // 約数についてのゼータ変換。 g_n = \Sigma_{m|n} f_m なる g を求める。
  template <typename T, T(*op)(T, T) >
  std::vector<T> zeta_transform_naive(const std::vector<T>& f) {
    int N = f.size() - 1;
    std::vector<T> g = f;

    for (int i = 1; i <= N; i++) {
      for (int j = 2 * i; j <= N; j += i) {
        g[j] = op(g[j], f[i]);
      }
    }

    return g;
  }

  // 約数についてのメビウス変換。 f_n = \Sigma_{m|n} g_m なる g を求める。
  template <typename T, T(*invop)(T, T)>
  std::vector<T> moebius_transform_naive(const std::vector<T>& f) {
    int N = f.size() - 1;
    std::vector<T> g = f;

    for (int i = 1; i <= N; i++) {
      for (int j = i * 2; j <= N; j += i) {
        g[j] = invop(g[j], g[i]);
      }
    }

    return g;
  }

  template <typename I, typename T, T(*op)(T, T)>
  std::map<I, T> zeta_transform(const std::map<I, T>& mp) {
    std::map<I, T> ret = mp;
    for (auto p2itr = mp.rbegin(); p2itr != mp.rend(); p2itr++) {
      for (auto p1itr = next(p2itr); p1itr != mp.rend(); p1itr++) {
        if ((*p2itr).first % (*p1itr).first == 0) {
          ret[(*p2itr).first] = op(ret[(*p2itr).first], ret[(*p1itr).first]);
        }
      }
    }

    return ret;
  }


  template <typename I, typename T, T(*op)(T, T)>
  std::map<I, T> moebius_transform(const std::map<I, T>& mp) {
    std::map<I, T> ret = mp;

    for (auto p1itr = ret.begin(); p1itr != ret.end(); p1itr++) {
      for (auto p2itr = next(p1itr); p2itr != ret.end(); p2itr++) {
        if ((*p2itr).first % (*p1itr).first == 0) {
          ret[(*p2itr).first] = invop(ret[(*p2itr).first], ret[(*p1itr).first]);
        }
      }
    }

    return ret;
  }
} // namespace divisor

#endif // HARUILIB_CONVOLUTION_DIVISOR_ZETA_MOEBIUS_TRANSFORM_HPP