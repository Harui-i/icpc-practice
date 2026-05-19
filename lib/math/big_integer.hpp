#ifndef HARUILIB_MATH_BIG_INTEGER_HPP
#define HARUILIB_MATH_BIG_INTEGER_HPP

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace big_integer_internal {

using ll = long long;

template<int MOD, int G>
struct NTT {
  static int mod_pow(int a, int e) {
    long long r = 1, x = a;
    while(e > 0) {
      if(e & 1) r = r * x % MOD;
      x = x * x % MOD;
      e >>= 1;
    }
    return (int)r;
  }

  static void ntt(std::vector<int>& a, bool inverse) {
    int n = (int)a.size();
    for(int i=1, j=0; i<n; i++) {
      int bit = n >> 1;
      for(; j & bit; bit >>= 1) j ^= bit;
      j ^= bit;
      if(i < j) std::swap(a[i], a[j]);
    }

    for(int len=2; len<=n; len<<=1) {
      int wlen = mod_pow(G, (MOD - 1) / len);
      if(inverse) wlen = mod_pow(wlen, MOD - 2);
      for(int i=0; i<n; i+=len) {
        long long w = 1;
        for(int j=0; j<len/2; j++) {
          int u = a[i + j];
          int v = (int)(w * a[i + j + len / 2] % MOD);
          int x = u + v; if(x >= MOD) x -= MOD;
          int y = u - v; if(y < 0) y += MOD;
          a[i + j] = x;
          a[i + j + len / 2] = y;
          w = w * wlen % MOD;
        }
      }
    }

    if(inverse) {
      int inv_n = mod_pow(n, MOD - 2);
      for(int& x: a) x = (int)((long long)x * inv_n % MOD);
    }
  }

  static std::vector<int> convolution(const std::vector<int>& a, const std::vector<int>& b) {
    if(a.empty() || b.empty()) return {};
    int need = (int)a.size() + (int)b.size() - 1;
    int n = 1;
    while(n < need) n <<= 1;
    std::vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);
    ntt(fa, false);
    ntt(fb, false);
    for(int i=0; i<n; i++) fa[i] = (int)((long long)fa[i] * fb[i] % MOD);
    ntt(fa, true);
    fa.resize(need);
    return fa;
  }
};

inline long long crt3(int x1, int x2, int x3) {
  static constexpr long long m1 = 998244353LL;
  static constexpr long long m2 = 1004535809LL;
  static constexpr long long m3 = 469762049LL;
  static const long long inv_m1_mod_m2 = NTT<1004535809, 3>::mod_pow((int)(m1 % m2), (int)m2 - 2);
  static const long long inv_m1m2_mod_m3 =
      NTT<469762049, 3>::mod_pow((int)((__int128)m1 * m2 % m3), (int)m3 - 2);

  long long t2 = (x2 - x1) % m2;
  if(t2 < 0) t2 += m2;
  t2 = t2 * inv_m1_mod_m2 % m2;

  long long x1_m3 = x1 % m3;
  long long cur_m3 = (x1_m3 + (__int128)(m1 % m3) * (t2 % m3)) % m3;
  long long t3 = (x3 - cur_m3) % m3;
  if(t3 < 0) t3 += m3;
  t3 = t3 * inv_m1m2_mod_m3 % m3;

  return (long long)(x1 + (__int128)m1 * t2 + (__int128)m1 * m2 * t3);
}

} // namespace big_integer_internal

struct BigInteger {
  using u32 = std::uint32_t;
  using u64 = std::uint64_t;
  using u128 = unsigned __int128;
  static constexpr u64 base = (1ULL << 32);

  std::vector<u32> a;
  int sign = 1;

  BigInteger() = default;
  BigInteger(long long v) { *this = v; }
  BigInteger(const std::string& s) { read(s); }

  BigInteger& operator=(long long v) {
    sign = v < 0 ? -1 : 1;
    u64 x = v < 0 ? (u64)(-(v + 1)) + 1 : (u64)v;
    a.clear();
    while(x > 0) {
      a.push_back((u32)x);
      x >>= 32;
    }
    trim();
    return *this;
  }

  bool is_zero() const { return a.empty(); }

  BigInteger& trim() {
    while(!a.empty() && a.back() == 0) a.pop_back();
    if(a.empty()) sign = 1;
    return *this;
  }

  BigInteger abs() const {
    BigInteger res = *this;
    res.sign = 1;
    return res;
  }

  void read(const std::string& s) {
    int sgn = 1;
    sign = 1;
    a.clear();
    int pos = 0;
    while(pos < (int)s.size() && std::isspace((unsigned char)s[pos])) pos++;
    if(pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
      if(s[pos] == '-') sgn = -1;
      pos++;
    }
    int end = pos;
    while(end < (int)s.size() && std::isdigit((unsigned char)s[end])) end++;
    std::vector<int> dec;
    for(int i=end; i>pos; i-=3) {
      int l = std::max(pos, i - 3);
      int x = 0;
      for(int j=l; j<i; j++) x = x * 10 + (s[j] - '0');
      dec.push_back(x);
    }
    *this = from_decimal_chunks(dec, 0, (int)dec.size());
    sign = sgn;
    trim();
  }

  std::string to_string() const {
    if(a.empty()) return "0";
    std::vector<int> parts = to_decimal_chunks(a, 0, (int)a.size());
    std::string s = sign < 0 ? "-" : "";
    s += std::to_string(parts.back());
    for(int i=(int)parts.size()-2; i>=0; i--) {
      std::string t = std::to_string(parts[i]);
      s += std::string(3 - (int)t.size(), '0') + t;
    }
    return s;
  }

  static int abs_compare(const BigInteger& x, const BigInteger& y) {
    if(x.a.size() != y.a.size()) return x.a.size() < y.a.size() ? -1 : 1;
    for(int i=(int)x.a.size()-1; i>=0; i--) {
      if(x.a[i] != y.a[i]) return x.a[i] < y.a[i] ? -1 : 1;
    }
    return 0;
  }

  friend bool operator<(const BigInteger& x, const BigInteger& y) {
    if(x.sign != y.sign) return x.sign < y.sign;
    int cmp = abs_compare(x, y);
    return x.sign == 1 ? cmp < 0 : cmp > 0;
  }
  friend bool operator==(const BigInteger& x, const BigInteger& y) {
    return x.sign == y.sign && x.a == y.a;
  }
  friend bool operator!=(const BigInteger& x, const BigInteger& y) { return !(x == y); }
  friend bool operator>(const BigInteger& x, const BigInteger& y) { return y < x; }
  friend bool operator<=(const BigInteger& x, const BigInteger& y) { return !(y < x); }
  friend bool operator>=(const BigInteger& x, const BigInteger& y) { return !(x < y); }

  BigInteger operator-() const {
    BigInteger res = *this;
    if(!res.is_zero()) res.sign = -res.sign;
    return res;
  }

  friend BigInteger operator+(BigInteger x, const BigInteger& y) {
    if(x.sign == y.sign) {
      u64 carry = 0;
      for(size_t i=0; i<std::max(x.a.size(), y.a.size()) || carry; i++) {
        if(i == x.a.size()) x.a.push_back(0);
        u64 cur = carry + x.a[i] + (i < y.a.size() ? y.a[i] : 0ULL);
        x.a[i] = (u32)cur;
        carry = cur >> 32;
      }
      return x;
    }
    return x - (-y);
  }

  friend BigInteger operator-(BigInteger x, const BigInteger& y) {
    if(y.is_zero()) return x;
    if(x.sign == y.sign) {
      if(abs_compare(x, y) >= 0) {
        u64 borrow = 0;
        for(size_t i=0; i<y.a.size() || borrow; i++) {
          u64 sub = borrow + (i < y.a.size() ? y.a[i] : 0ULL);
          u64 cur = x.a[i];
          x.a[i] = (u32)(cur - sub);
          borrow = cur < sub;
        }
        return x.trim();
      }
      return -(y - x);
    }
    return x + (-y);
  }

  static std::vector<u32> multiply_digits(const std::vector<u32>& x, const std::vector<u32>& y) {
    if(x.empty() || y.empty()) return {};
    if(std::min(x.size(), y.size()) <= 60) {
      std::vector<u128> tmp(x.size() + y.size());
      for(size_t i=0; i<x.size(); i++) for(size_t j=0; j<y.size(); j++) {
        tmp[i + j] += (u128)x[i] * y[j];
      }
      std::vector<u32> res(tmp.size());
      u128 carry = 0;
      for(size_t i=0; i<tmp.size(); i++) {
        u128 cur = tmp[i] + carry;
        res[i] = (u32)cur;
        carry = cur >> 32;
      }
      while(carry > 0) {
        res.push_back((u32)carry);
        carry >>= 32;
      }
      while(!res.empty() && res.back() == 0) res.pop_back();
      return res;
    }

    auto split = [](const std::vector<u32>& v) {
      std::vector<int> res;
      res.reserve(v.size() * 4);
      for(u32 x: v) {
        res.push_back((int)(x & 255));
        res.push_back((int)((x >> 8) & 255));
        res.push_back((int)((x >> 16) & 255));
        res.push_back((int)(x >> 24));
      }
      while(!res.empty() && res.back() == 0) res.pop_back();
      return res;
    };

    using N1 = big_integer_internal::NTT<998244353, 3>;
    using N2 = big_integer_internal::NTT<1004535809, 3>;
    using N3 = big_integer_internal::NTT<469762049, 3>;
    std::vector<int> sx = split(x), sy = split(y);
    std::vector<int> c1 = N1::convolution(sx, sy);
    std::vector<int> c2 = N2::convolution(sx, sy);
    std::vector<int> c3 = N3::convolution(sx, sy);
    std::vector<int> chunks(c1.size());
    long long carry = 0;
    for(size_t i=0; i<c1.size(); i++) {
      long long cur = big_integer_internal::crt3(c1[i], c2[i], c3[i]) + carry;
      chunks[i] = (int)(cur & 255);
      carry = cur >> 8;
    }
    while(carry > 0) {
      chunks.push_back((int)(carry & 255));
      carry >>= 8;
    }

    std::vector<u32> res;
    res.reserve((chunks.size() + 3) / 4);
    for(size_t i=0; i<chunks.size(); i+=4) {
      u32 cur = (u32)chunks[i];
      if(i + 1 < chunks.size()) cur |= (u32)chunks[i + 1] << 8;
      if(i + 2 < chunks.size()) cur |= (u32)chunks[i + 2] << 16;
      if(i + 3 < chunks.size()) cur |= (u32)chunks[i + 3] << 24;
      res.push_back(cur);
    }
    while(!res.empty() && res.back() == 0) res.pop_back();
    return res;
  }

  static std::vector<int> decimal_add(std::vector<int> x, const std::vector<int>& y) {
    int carry = 0;
    for(size_t i=0; i<std::max(x.size(), y.size()) || carry; i++) {
      if(i == x.size()) x.push_back(0);
      int cur = x[i] + carry + (i < y.size() ? y[i] : 0);
      if(cur >= 1000) {
        cur -= 1000;
        carry = 1;
      } else {
        carry = 0;
      }
      x[i] = cur;
    }
    while(!x.empty() && x.back() == 0) x.pop_back();
    return x;
  }

  static std::vector<int> decimal_mul(const std::vector<int>& x, const std::vector<int>& y) {
    if(x.empty() || y.empty()) return {};
    if(std::min(x.size(), y.size()) <= 80) {
      std::vector<long long> tmp(x.size() + y.size());
      for(size_t i=0; i<x.size(); i++) for(size_t j=0; j<y.size(); j++) {
        tmp[i + j] += (long long)x[i] * y[j];
      }
      std::vector<int> res(tmp.size());
      long long carry = 0;
      for(size_t i=0; i<tmp.size(); i++) {
        long long cur = tmp[i] + carry;
        res[i] = (int)(cur % 1000);
        carry = cur / 1000;
      }
      while(carry > 0) {
        res.push_back((int)(carry % 1000));
        carry /= 1000;
      }
      while(!res.empty() && res.back() == 0) res.pop_back();
      return res;
    }

    using N1 = big_integer_internal::NTT<998244353, 3>;
    using N2 = big_integer_internal::NTT<1004535809, 3>;
    using N3 = big_integer_internal::NTT<469762049, 3>;
    std::vector<int> c1 = N1::convolution(x, y);
    std::vector<int> c2 = N2::convolution(x, y);
    std::vector<int> c3 = N3::convolution(x, y);
    std::vector<int> res(c1.size());
    long long carry = 0;
    for(size_t i=0; i<c1.size(); i++) {
      long long cur = big_integer_internal::crt3(c1[i], c2[i], c3[i]) + carry;
      res[i] = (int)(cur % 1000);
      carry = cur / 1000;
    }
    while(carry > 0) {
      res.push_back((int)(carry % 1000));
      carry /= 1000;
    }
    while(!res.empty() && res.back() == 0) res.pop_back();
    return res;
  }

  static std::vector<int> decimal_from_u64(u64 x) {
    std::vector<int> res;
    while(x > 0) {
      res.push_back((int)(x % 1000));
      x /= 1000;
    }
    return res;
  }

  static BigInteger pow1000_chunks(int n) {
    static std::unordered_map<int, BigInteger> cache;
    auto it = cache.find(n);
    if(it != cache.end()) return it->second;
    BigInteger res;
    if(n == 0) {
      res = 1;
    } else if(n == 1) {
      res = 1000;
    } else {
      int m = n >> 1;
      res = pow1000_chunks(m) * pow1000_chunks(n - m);
    }
    cache.emplace(n, res);
    return res;
  }

  static BigInteger from_decimal_chunks(const std::vector<int>& dec, int l, int r) {
    if(l >= r) return BigInteger(0);
    if(r - l == 1) return BigInteger(dec[l]);
    int m = (l + r) >> 1;
    BigInteger low = from_decimal_chunks(dec, l, m);
    BigInteger high = from_decimal_chunks(dec, m, r);
    return low + high * pow1000_chunks(m - l);
  }

  static std::vector<int> pow2_decimal_chunks(int n) {
    static std::unordered_map<int, std::vector<int>> cache;
    auto it = cache.find(n);
    if(it != cache.end()) return it->second;
    std::vector<int> res;
    if(n == 0) {
      res = {1};
    } else if(n == 1) {
      res = decimal_from_u64(base);
    } else {
      int m = n >> 1;
      res = decimal_mul(pow2_decimal_chunks(m), pow2_decimal_chunks(n - m));
    }
    cache.emplace(n, res);
    return res;
  }

  static std::vector<int> to_decimal_chunks(const std::vector<u32>& limbs, int l, int r) {
    if(l >= r) return {};
    if(r - l == 1) return decimal_from_u64(limbs[l]);
    int m = (l + r) >> 1;
    std::vector<int> low = to_decimal_chunks(limbs, l, m);
    std::vector<int> high = to_decimal_chunks(limbs, m, r);
    return decimal_add(low, decimal_mul(high, pow2_decimal_chunks(m - l)));
  }

  friend BigInteger operator*(const BigInteger& x, const BigInteger& y) {
    BigInteger res;
    res.sign = x.sign * y.sign;
    res.a = multiply_digits(x.a, y.a);
    return res.trim();
  }

  BigInteger& operator+=(const BigInteger& v) { return *this = *this + v; }
  BigInteger& operator-=(const BigInteger& v) { return *this = *this - v; }
  BigInteger& operator*=(const BigInteger& v) { return *this = *this * v; }

  void add_uint(u32 v) {
    u64 carry = v;
    for(size_t i=0; carry; i++) {
      if(i == a.size()) a.push_back(0);
      u64 cur = (u64)a[i] + carry;
      a[i] = (u32)cur;
      carry = cur >> 32;
    }
  }

  void mul_uint(u32 m) {
    if(m == 0 || is_zero()) {
      a.clear();
      sign = 1;
      return;
    }
    u64 carry = 0;
    for(size_t i=0; i<a.size() || carry; i++) {
      if(i == a.size()) a.push_back(0);
      u64 cur = carry + (u64)a[i] * m;
      a[i] = (u32)cur;
      carry = cur >> 32;
    }
    trim();
  }

  u32 div_uint(u32 v) {
    assert(v > 0);
    u64 rem = 0;
    for(int i=(int)a.size()-1; i>=0; i--) {
      u64 cur = (rem << 32) | a[i];
      a[i] = (u32)(cur / v);
      rem = cur % v;
    }
    trim();
    return (u32)rem;
  }

  void shl_bits(int s) {
    if(s == 0 || is_zero()) return;
    u32 carry = 0;
    for(size_t i=0; i<a.size(); i++) {
      u32 next = s == 0 ? 0 : (a[i] >> (32 - s));
      a[i] = (a[i] << s) | carry;
      carry = next;
    }
    if(carry) a.push_back(carry);
  }

  void shr_bits(int s) {
    if(s == 0 || is_zero()) return;
    u32 carry = 0;
    for(int i=(int)a.size()-1; i>=0; i--) {
      u32 next = a[i] << (32 - s);
      a[i] = (a[i] >> s) | carry;
      carry = next;
    }
    trim();
  }

  static std::pair<BigInteger, BigInteger> divmod_abs(BigInteger u, BigInteger v) {
    assert(!v.is_zero());
    if(abs_compare(u, v) < 0) return {BigInteger(0), u};
    if(v.a.size() == 1) {
      BigInteger q = u;
      u32 r = q.div_uint(v.a[0]);
      return {q, BigInteger(r)};
    }

    int shift = __builtin_clz(v.a.back());
    u.shl_bits(shift);
    v.shl_bits(shift);
    u.a.push_back(0);

    int n = (int)v.a.size();
    int m = (int)u.a.size() - n - 1;
    BigInteger q;
    q.a.assign(m + 1, 0);

    for(int j=m; j>=0; j--) {
      u128 numerator = ((u128)u.a[j + n] << 32) | u.a[j + n - 1];
      u64 qhat = (u64)(numerator / v.a[n - 1]);
      u64 rhat = (u64)(numerator % v.a[n - 1]);
      if(qhat == base) qhat--;

      while(n >= 2 && (u128)qhat * v.a[n - 2] > ((u128)rhat << 32) + u.a[j + n - 2]) {
        qhat--;
        rhat += v.a[n - 1];
        if(rhat >= base) break;
      }

      u64 borrow = 0;
      u64 carry = 0;
      for(int i=0; i<n; i++) {
        u128 prod = (u128)qhat * v.a[i] + carry;
        carry = (u64)(prod >> 32);
        u64 low = (u32)prod;
        u64 sub = low + borrow;
        u64 cur = u.a[j + i];
        u.a[j + i] = (u32)(cur - sub);
        borrow = (cur < sub);
      }
      u64 sub = carry + borrow;
      u64 cur = u.a[j + n];
      u.a[j + n] = (u32)(cur - sub);
      bool negative = cur < sub;

      if(negative) {
        qhat--;
        u64 c = 0;
        for(int i=0; i<n; i++) {
          u64 sum = (u64)u.a[j + i] + v.a[i] + c;
          u.a[j + i] = (u32)sum;
          c = sum >> 32;
        }
        u.a[j + n] += (u32)c;
      }
      q.a[j] = (u32)qhat;
    }

    q.trim();
    u.shr_bits(shift);
    u.trim();
    return {q, u};
  }

  friend std::pair<BigInteger, BigInteger> divmod(const BigInteger& x, const BigInteger& y) {
    assert(!y.is_zero());
    auto [q, r] = divmod_abs(x.abs(), y.abs());
    q.sign = x.sign * y.sign;
    r.sign = x.sign;
    q.trim();
    r.trim();
    return {q, r};
  }

  friend BigInteger operator/(const BigInteger& x, const BigInteger& y) {
    return divmod(x, y).first;
  }
  friend BigInteger operator%(const BigInteger& x, const BigInteger& y) {
    return divmod(x, y).second;
  }
  BigInteger& operator/=(const BigInteger& v) { return *this = *this / v; }
  BigInteger& operator%=(const BigInteger& v) { return *this = *this % v; }

  friend std::istream& operator>>(std::istream& is, BigInteger& v) {
    std::string s;
    is >> s;
    v.read(s);
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const BigInteger& v) {
    return os << v.to_string();
  }
};

#endif // HARUILIB_MATH_BIG_INTEGER_HPP
