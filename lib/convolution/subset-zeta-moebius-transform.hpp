#ifndef HARUILIB_CONVOLUTION_SUBSET_ZETA_MOEBIUS_TRANSFORM_HPP
#define HARUILIB_CONVOLUTION_SUBSET_ZETA_MOEBIUS_TRANSFORM_HPP

#include <vector>

template <class T, T (*op)(T, T) >
std::vector<T> subset_zeta_transform(const std::vector<T>& f) {

  int n = 0; while ((1 << n) < (int)f.size()) n++;
  assert((int)f.size() == (1 << n)); // f.size() should be power of 2.


  std::vector<T> F = f;
  for (int k = 0; k < n; k++) {
    for (int s = 0; s < 1 << n; s++) {
      if ((s >> k) & 1) F[s] = op(F[s], F[s ^ (1 << k)]);
    }
  }
  return F;
}


template <class T, T (*invop)(T, T) >
std::vector<T> subset_moebius_transform(const std::vector<T>& f) {
  int n = 0; while ((1 << n) < (int)f.size()) n++;
  assert((int)f.size() == (1 << n)); // f.size() should be power of 2.

  std::vector<T> F = f;
  for (int k = 0; k < n; k++) {
    for (int s = 0; s < 1 << n; s++) {
      if ((s >> k) & 1) F[s] = invop(F[s], F[s ^ (1 << k)]);
    }
  }
  return F;
}

#endif // HARUILIB_CONVOLUTION_SUBSET_ZETA_MOEBIUS_TRANSFORM_HPP