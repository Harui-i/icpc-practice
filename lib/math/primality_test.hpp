#ifndef HARUILIB_MATH_PRIMALITY_TEST_HPP
#define HARUILIB_MATH_PRIMALITY_TEST_HPP

#include <cstdint>

namespace primality_test_internal {

using u64 = unsigned long long;
using u128 = unsigned __int128;

inline u64 mod_pow_u64(u64 a, u64 e, u64 mod) {
  u64 ret = 1;
  while(e > 0) {
    if(e & 1) ret = (u128)ret * a % mod;
    a = (u128)a * a % mod;
    e >>= 1;
  }
  return ret;
}

inline bool miller_rabin(u64 n, u64 a, u64 d, int s) {
  if(a % n == 0) return true;
  u64 x = mod_pow_u64(a, d, n);
  if(x == 1 || x == n - 1) return true;
  for(int i=1; i<s; i++) {
    x = (u128)x * x % n;
    if(x == n - 1) return true;
  }
  return false;
}

} // namespace primality_test_internal

inline bool is_prime(unsigned long long n) {
  using namespace primality_test_internal;
  if(n < 2) return false;
  for(u64 p: {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
    if(n == p) return true;
    if(n % p == 0) return false;
  }

  u64 d = n - 1;
  int s = 0;
  while((d & 1) == 0) {
    d >>= 1;
    s++;
  }

  for(u64 a: {2ULL, 3ULL, 5ULL, 7ULL, 11ULL, 13ULL, 17ULL, 19ULL, 23ULL, 29ULL, 31ULL, 37ULL}) {
    if(!miller_rabin(n, a, d, s)) return false;
  }
  return true;
}

#endif // HARUILIB_MATH_PRIMALITY_TEST_HPP
