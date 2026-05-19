#include <vector>
#include "formal-power-series/formal-power-series.hpp"

// AtCoderではverifyできたが、LCではできず
// given linear recurrence sequence a_{n+K}= c_1 a_{n+K-1} + c_2 a_{n+k-2} + \dots + c_{K-1} a_{n+1} + c_K a_n
// a_0, a_1, \dots, a_{K-1} are given
// calculate a_N (N-th term of linear recurrence sequence) time complexity is O(K log K log N) (when NNT is used), O(K^2 log N) (when naive convolution is used).
template <typename mint> 
mint Fiduccia(const vector<mint>& a, const vector<mint>& c, unsigned long long  N) {
  if (N < a.size()) return a[N];
  assert(a.size() == c.size());
  int K = c.size();

  FPS<mint> varphi(K+1); 
  varphi[K] = mint(1);
  for(int i=0; i<K; i++) varphi[i] = mint(-1) * c[K-i-1];

  // calculate x^N mod varphi, using square and multiply technique.
  // Note that there is two way to implement the methodlogy. LSB-first algorithm(famous one ) and MSB-first alogirthm.
 int msb=0;
  for (int i=0; 1ULL<< i <=N; i++) {
    if (N & (1ULL << i)) msb = i;
  }
  FPS<mint> remainder(1); remainder[0] = mint(1);
  for (int i=msb; i>=0; i--) {
    if (N & (1ULL << i)) {
      remainder = remainder << 1; // it is equal to remainder *= x.
      if (remainder.size() >= varphi.size()) remainder %= varphi;
    }
    if (i != 0) {
      remainder *= remainder; // NTTなら、NTT配列を使い回すことで定数倍が良くなるね
      if (remainder.size() >= varphi.size()) remainder %= varphi;
    }
  }

  // remainder = x^N mod varphi 
  mint ret = 0;
  assert(remainder.size() <= K);
  for(int i=0; i<remainder.size(); i++) {
    ret += remainder[i] * a[i];
  }

  return ret;
}
