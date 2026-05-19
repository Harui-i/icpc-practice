#ifndef HARUILIB_MATH_COUNT_BY_REMAINDER_HPP
#define HARUILIB_MATH_COUNT_BY_REMAINDER_HPP

template <typename T= long long>
// l以上r未満で、Mで割った余りがbである整数の個数を求める
T count_by_remainder(T l, T r, T b, T M) {
  assert(l <= r && 0 <= b && b < M);
  r--;
  T k_min = (l - b + M - 1) / M;
  if (l - b + M - 1 < 0 && (l - b + M - 1) % M != 0) k_min--;

  T k_max = (r - b) / M;
  if (r - b < 0 && (r - b) % M != 0) k_max--;

  T ans = k_max - k_min + 1;
  //T mini = k_min * M + b;
  //T maxi = k_max * M + b;

  return ans;
}


#endif // HARUILIB_MATH_COUNT_BY_REMAINDER_HPP