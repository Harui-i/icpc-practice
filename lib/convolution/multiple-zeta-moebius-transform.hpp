#ifndef HARUILIB_CONVOLUTION_MULTIPLE_ZETA_MOEBIUS_TRANSFORM_HPP
#define HARUILIB_CONVOLUTION_MULTIPLE_ZETA_MOEBIUS_TRANSFORM_HPP

#include <vector>
#include <map>

namespace multiple {

  // 倍数についてのゼータ変換。 g_n = \Sigma_{n|m} f_m なる g を求める。
  // n|mというのは、m%n==0という意味。
  // O(N log N) (調和級数)
  // うまくやるとO(Nlog(log(N)))にできることがよく知られているが、難しいしlogは定数なので妥協する。
  template <typename T, T (*op)(T, T)>
  std::vector<T> zeta_transform_naive(const std::vector<T>& f) {
    int N = f.size() - 1;
    std::vector<T> g = f;
    for (int i = 1; i <= N; i++) {
      for (int j = 2 * i; j <= N; j += i) {
        g[i] = op(g[i], f[j]);
      }
    }

    return g;
  }

  // 倍数についてのメビウス変換
  // f_n = \Sigma_{n|m} g_m なる g を求める。
  // O(N log N) (調和級数)
  template <typename T, T(*invop)(T, T)>
  std::vector<T> moebius_transform_naive(const std::vector<T>& f) {
    int N = f.size() - 1;
    std::vector<T> g = f;
    for (int i = N; i >= 1; i--) {
      for (int j = 2 * i; j <= N; j += i) {
        g[i] = invop(g[i], g[j]);
      }
    }
    return g;
  }


  template <typename I, typename T, T(*op)(T, T)>
  std::map<I, T> zeta_transform(const std::map<I, T>& mp) {
    std::map<I, T> ret = mp;
    for (std::pair<I, T> pit : ret) {
      for (auto p2itr = ret.rbegin(); (*p2itr).first != pit.first; p2itr++) {
        if ((*p2itr).first % pit.first == 0) {
          ret[pit.first] = op(ret[pit.first], (*p2itr).second);
        }
      }
    }

    return ret;
  }


  template <typename I, typename T, T (*invop)(T, T)>
  std::map<I, T> moebius_transform(const std::map<I, T>& mp) {
    std::map<I, T> ret = mp;
    for (auto p1itr = ret.rbegin(); p1itr != ret.rend(); p1itr++) {
      for (auto p2itr = ret.rbegin(); p2itr != p1itr; p2itr++) {
        if ((*p2itr).first % (*p1itr).first == 0) {
          (*p1itr).second = invop((*p1itr).second, (*p2itr).second);
        }
      }
    }

    return ret;
  }

} // namespace multiple

#endif // HARUILIB_CONVOLUTION_MULTIPLE_ZETA_MOEBIUS_TRANSFORM_HPP