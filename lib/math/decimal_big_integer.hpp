#ifndef HARUILIB_MATH_DECIMAL_BIG_INTEGER_HPP
#define HARUILIB_MATH_DECIMAL_BIG_INTEGER_HPP

#include <algorithm>
#include <cassert>
#include <cctype>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace decimal_big_integer_internal {

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

  long long cur_m3 = (x1 % m3 + (__int128)(m1 % m3) * (t2 % m3)) % m3;
  long long t3 = (x3 - cur_m3) % m3;
  if(t3 < 0) t3 += m3;
  t3 = t3 * inv_m1m2_mod_m3 % m3;

  __int128 res = x1 + (__int128)m1 * t2 + (__int128)m1 * m2 * t3;
  return (long long)res;
}

} // namespace decimal_big_integer_internal

struct DecimalBigInteger {
  using i128 = __int128;
  static constexpr long long base = 1000000000000000000LL;
  static constexpr int base_digits = 18;
  std::vector<long long> a;
  int sign = 1;

  DecimalBigInteger() = default;
  DecimalBigInteger(long long v) { *this = v; }
  DecimalBigInteger(const std::string& s) { read(s); }

  DecimalBigInteger& operator=(long long v) {
    sign = v < 0 ? -1 : 1;
    unsigned long long x = v < 0 ? (unsigned long long)(-(v + 1)) + 1 : (unsigned long long)v;
    a.clear();
    while(x > 0) {
      a.push_back((long long)(x % base));
      x /= base;
    }
    trim();
    return *this;
  }

  bool is_zero() const { return a.empty(); }

  DecimalBigInteger& trim() {
    while(!a.empty() && a.back() == 0) a.pop_back();
    if(a.empty()) sign = 1;
    return *this;
  }

  DecimalBigInteger abs() const {
    DecimalBigInteger res = *this;
    res.sign = 1;
    return res;
  }

  void read(const std::string& s) {
    sign = 1;
    a.clear();
    int pos = 0;
    while(pos < (int)s.size() && std::isspace((unsigned char)s[pos])) pos++;
    if(pos < (int)s.size() && (s[pos] == '-' || s[pos] == '+')) {
      if(s[pos] == '-') sign = -1;
      pos++;
    }
    int end = pos;
    while(end < (int)s.size() && std::isdigit((unsigned char)s[end])) end++;
    for(int i=end; i>pos; i-=base_digits) {
      int l = std::max(pos, i - base_digits);
      long long x = 0;
      for(int j=l; j<i; j++) x = x * 10 + (s[j] - '0');
      a.push_back(x);
    }
    trim();
  }

  std::string to_string() const {
    if(a.empty()) return "0";
    std::string s = sign < 0 ? "-" : "";
    s += std::to_string(a.back());
    for(int i=(int)a.size()-2; i>=0; i--) {
      std::string t = std::to_string(a[i]);
      s += std::string(base_digits - (int)t.size(), '0') + t;
    }
    return s;
  }

  static int abs_compare(const DecimalBigInteger& x, const DecimalBigInteger& y) {
    if(x.a.size() != y.a.size()) return x.a.size() < y.a.size() ? -1 : 1;
    for(int i=(int)x.a.size()-1; i>=0; i--) {
      if(x.a[i] != y.a[i]) return x.a[i] < y.a[i] ? -1 : 1;
    }
    return 0;
  }

  friend bool operator<(const DecimalBigInteger& x, const DecimalBigInteger& y) {
    if(x.sign != y.sign) return x.sign < y.sign;
    int cmp = abs_compare(x, y);
    return x.sign == 1 ? cmp < 0 : cmp > 0;
  }
  friend bool operator==(const DecimalBigInteger& x, const DecimalBigInteger& y) {
    return x.sign == y.sign && x.a == y.a;
  }
  friend bool operator!=(const DecimalBigInteger& x, const DecimalBigInteger& y) { return !(x == y); }
  friend bool operator>(const DecimalBigInteger& x, const DecimalBigInteger& y) { return y < x; }
  friend bool operator<=(const DecimalBigInteger& x, const DecimalBigInteger& y) { return !(y < x); }
  friend bool operator>=(const DecimalBigInteger& x, const DecimalBigInteger& y) { return !(x < y); }

  DecimalBigInteger operator-() const {
    DecimalBigInteger res = *this;
    if(!res.is_zero()) res.sign = -res.sign;
    return res;
  }

  friend DecimalBigInteger operator+(DecimalBigInteger x, const DecimalBigInteger& y) {
    if(x.sign == y.sign) {
      int carry = 0;
      for(size_t i=0; i<std::max(x.a.size(), y.a.size()) || carry; i++) {
        if(i == x.a.size()) x.a.push_back(0);
        long long cur = (long long)x.a[i] + carry + (i < y.a.size() ? y.a[i] : 0);
        carry = cur >= base;
        if(carry) cur -= base;
        x.a[i] = cur;
      }
      return x;
    }
    return x - (-y);
  }

  friend DecimalBigInteger operator-(DecimalBigInteger x, const DecimalBigInteger& y) {
    if(y.is_zero()) return x;
    if(x.sign == y.sign) {
      if(abs_compare(x, y) >= 0) {
        int carry = 0;
        for(size_t i=0; i<y.a.size() || carry; i++) {
          long long cur = (long long)x.a[i] - carry - (i < y.a.size() ? y.a[i] : 0);
          carry = cur < 0;
          if(carry) cur += base;
          x.a[i] = cur;
        }
        return x.trim();
      }
      return -(y - x);
    }
    return x + (-y);
  }

  static std::vector<int> to_base1000000(const std::vector<long long>& v) {
    std::vector<int> res;
    res.reserve(v.size() * 3);
    for(long long x: v) {
      for(int i=0; i<3; i++) {
        res.push_back((int)(x % 1000000));
        x /= 1000000;
      }
    }
    while(!res.empty() && res.back() == 0) res.pop_back();
    return res;
  }

  static std::vector<long long> multiply_digits(const std::vector<long long>& x, const std::vector<long long>& y) {
    if(x.empty() || y.empty()) return {};
    if(std::min(x.size(), y.size()) <= 32) {
      std::vector<i128> tmp(x.size() + y.size());
      for(size_t i=0; i<x.size(); i++) for(size_t j=0; j<y.size(); j++) {
        tmp[i + j] += (i128)x[i] * y[j];
      }
      std::vector<long long> res(tmp.size());
      i128 carry = 0;
      for(size_t i=0; i<tmp.size(); i++) {
        i128 cur = tmp[i] + carry;
        res[i] = (long long)(cur % base);
        carry = cur / base;
      }
      while(carry > 0) {
        res.push_back((long long)(carry % base));
        carry /= base;
      }
      while(!res.empty() && res.back() == 0) res.pop_back();
      return res;
    }

    using N1 = decimal_big_integer_internal::NTT<998244353, 3>;
    using N2 = decimal_big_integer_internal::NTT<1004535809, 3>;
    using N3 = decimal_big_integer_internal::NTT<469762049, 3>;
    std::vector<int> sx = to_base1000000(x), sy = to_base1000000(y);
    std::vector<int> c1 = N1::convolution(sx, sy);
    std::vector<int> c2 = N2::convolution(sx, sy);
    std::vector<int> c3 = N3::convolution(sx, sy);

    std::vector<int> chunks(c1.size());
    long long carry = 0;
    for(size_t i=0; i<c1.size(); i++) {
      long long cur = decimal_big_integer_internal::crt3(c1[i], c2[i], c3[i]) + carry;
      chunks[i] = (int)(cur % 1000000);
      carry = cur / 1000000;
    }
    while(carry > 0) {
      chunks.push_back((int)(carry % 1000000));
      carry /= 1000000;
    }

    std::vector<long long> res;
    res.reserve((chunks.size() + 2) / 3);
    for(size_t i=0; i<chunks.size(); i+=3) {
      long long cur = 0;
      long long p = 1;
      for(size_t j=0; j<3 && i+j<chunks.size(); j++) {
        cur += (long long)chunks[i + j] * p;
        p *= 1000000;
      }
      res.push_back(cur);
    }
    while(!res.empty() && res.back() == 0) res.pop_back();
    return res;
  }

  friend DecimalBigInteger operator*(const DecimalBigInteger& x, const DecimalBigInteger& y) {
    DecimalBigInteger res;
    res.sign = x.sign * y.sign;
    res.a = multiply_digits(x.a, y.a);
    return res.trim();
  }

  DecimalBigInteger& operator+=(const DecimalBigInteger& v) { return *this = *this + v; }
  DecimalBigInteger& operator-=(const DecimalBigInteger& v) { return *this = *this - v; }
  DecimalBigInteger& operator*=(const DecimalBigInteger& v) { return *this = *this * v; }

  void mul_int(long long m) {
    if(m == 0 || is_zero()) {
      a.clear();
      sign = 1;
      return;
    }
    i128 carry = 0;
    for(size_t i=0; i<a.size() || carry; i++) {
      if(i == a.size()) a.push_back(0);
      i128 cur = carry + (i128)a[i] * m;
      a[i] = (long long)(cur % base);
      carry = cur / base;
    }
    trim();
  }

  long long div_int(long long v) {
    assert(v > 0);
    i128 rem = 0;
    for(int i=(int)a.size()-1; i>=0; i--) {
      i128 cur = a[i] + rem * base;
      a[i] = (long long)(cur / v);
      rem = cur % v;
    }
    trim();
    return (long long)rem;
  }

  static DecimalBigInteger digits_slice(const DecimalBigInteger& x, int l, int r) {
    DecimalBigInteger res;
    l = std::max(l, 0);
    r = std::min(r, (int)x.a.size());
    if(l < r) res.a.assign(x.a.begin() + l, x.a.begin() + r);
    return res.trim();
  }

  static DecimalBigInteger shift_left_digits(const DecimalBigInteger& x, int k) {
    if(x.is_zero()) return x;
    DecimalBigInteger res;
    res.a.assign(k, 0);
    res.a.insert(res.a.end(), x.a.begin(), x.a.end());
    return res;
  }

  static DecimalBigInteger low_digits(const DecimalBigInteger& x, int k) {
    return digits_slice(x, 0, k);
  }

  static DecimalBigInteger high_digits(const DecimalBigInteger& x, int k) {
    return digits_slice(x, k, (int)x.a.size());
  }

  static DecimalBigInteger one_shift_digits_minus_one(int k) {
    DecimalBigInteger res;
    res.a.assign(k, base - 1);
    return res.trim();
  }

  static std::pair<DecimalBigInteger, DecimalBigInteger> divmod_abs_knuth(DecimalBigInteger u, DecimalBigInteger v) {
    assert(!v.is_zero());
    if(abs_compare(u, v) < 0) return {DecimalBigInteger(0), u};
    if(v.a.size() == 1) {
      DecimalBigInteger q = u;
      long long r = q.div_int(v.a[0]);
      return {q, DecimalBigInteger(r)};
    }

    long long norm = base / (v.a.back() + 1);
    u.mul_int(norm);
    v.mul_int(norm);
    u.a.push_back(0);

    int n = (int)v.a.size();
    int m = (int)u.a.size() - n - 1;
    DecimalBigInteger q;
    q.a.assign(m + 1, 0);

    for(int j=m; j>=0; j--) {
      i128 numerator = (i128)u.a[j + n] * base + u.a[j + n - 1];
      long long qhat = (long long)(numerator / v.a[n - 1]);
      i128 rhat = numerator % v.a[n - 1];
      if(qhat >= base) {
        qhat = base - 1;
        rhat += v.a[n - 1];
      }

      while(n >= 2 && (i128)qhat * v.a[n - 2] > rhat * base + u.a[j + n - 2]) {
        qhat--;
        rhat += v.a[n - 1];
        if(rhat >= base) break;
      }

      i128 carry = 0;
      long long borrow = 0;
      for(int i=0; i<n; i++) {
        i128 prod = (i128)qhat * v.a[i] + carry;
        carry = prod / base;
        i128 cur = (i128)u.a[j + i] - (prod % base) - borrow;
        borrow = 0;
        if(cur < 0) {
          cur += base;
          borrow = 1;
        }
        u.a[j + i] = (long long)cur;
      }

      i128 cur = (i128)u.a[j + n] - carry - borrow;
      bool negative = cur < 0;
      if(negative) cur += base;
      u.a[j + n] = (long long)cur;

      if(negative) {
        qhat--;
        long long c = 0;
        for(int i=0; i<n; i++) {
          i128 sum = (i128)u.a[j + i] + v.a[i] + c;
          if(sum >= base) {
            sum -= base;
            c = 1;
          } else {
            c = 0;
          }
          u.a[j + i] = (long long)sum;
        }
        u.a[j + n] += c;
        if(u.a[j + n] >= base) u.a[j + n] -= base;
      }
      q.a[j] = qhat;
    }

    q.trim();
    u.div_int(norm);
    u.trim();
    return {q, u};
  }

  static std::pair<DecimalBigInteger, DecimalBigInteger> div_3n_2n(
      const DecimalBigInteger& a1,
      const DecimalBigInteger& a2,
      const DecimalBigInteger& a3,
      const DecimalBigInteger& b1,
      const DecimalBigInteger& b2,
      int n) {
    DecimalBigInteger q, r;
    int cmp = abs_compare(a1, b1);
    if(cmp >= 0) {
      q = one_shift_digits_minus_one(n);
      r = shift_left_digits(a1 - b1, n) + a2 + b1;
    } else {
      DecimalBigInteger top = shift_left_digits(a1, n) + a2;
      std::tie(q, r) = div_2n_1n(top, b1);
    }

    DecimalBigInteger b = shift_left_digits(b1, n) + b2;
    DecimalBigInteger r_full = shift_left_digits(r, n) + a3;
    r_full -= q * b2;
    while(r_full.sign < 0) {
      q -= DecimalBigInteger(1);
      r_full += b;
    }
    while(abs_compare(r_full, b) >= 0) {
      q += DecimalBigInteger(1);
      r_full -= b;
    }
    return {q.trim(), r_full.trim()};
  }

  static std::pair<DecimalBigInteger, DecimalBigInteger> div_2n_1n(const DecimalBigInteger& u, const DecimalBigInteger& v) {
    int n = (int)v.a.size();
    assert(n > 0);
    if(abs_compare(u, v) < 0) return {DecimalBigInteger(0), u};
    if(n <= 64) return divmod_abs_knuth(u, v);
    if(n & 1) {
      auto [q, r] = div_2n_1n(shift_left_digits(u, 1), shift_left_digits(v, 1));
      r = high_digits(r, 1);
      return {q.trim(), r.trim()};
    }

    int half = n / 2;
    DecimalBigInteger b1 = high_digits(v, half);
    DecimalBigInteger b2 = low_digits(v, half);

    DecimalBigInteger a1 = digits_slice(u, 3 * half, 4 * half);
    DecimalBigInteger a2 = digits_slice(u, 2 * half, 3 * half);
    DecimalBigInteger a3 = digits_slice(u, half, 2 * half);
    DecimalBigInteger a4 = digits_slice(u, 0, half);

    auto [q1, r1] = div_3n_2n(a1, a2, a3, b1, b2, half);
    DecimalBigInteger r1_high = high_digits(r1, half);
    DecimalBigInteger r1_low = low_digits(r1, half);
    auto [q2, r2] = div_3n_2n(r1_high, r1_low, a4, b1, b2, half);
    DecimalBigInteger q = shift_left_digits(q1, half) + q2;
    return {q.trim(), r2.trim()};
  }

  static std::pair<DecimalBigInteger, DecimalBigInteger> divmod_abs_bz(DecimalBigInteger u, DecimalBigInteger v) {
    int n = (int)v.a.size();
    if(n <= 128 || (n & 1)) return divmod_abs_knuth(std::move(u), std::move(v));

    DecimalBigInteger q, r;
    int blocks = ((int)u.a.size() + n - 1) / n;
    for(int block=blocks-1; block>=0; block--) {
      DecimalBigInteger cur = digits_slice(u, block * n, std::min((block + 1) * n, (int)u.a.size()));
      r = shift_left_digits(r, n) + cur;
      auto [q_block, next_r] = div_2n_1n(r, v);
      q += shift_left_digits(q_block, block * n);
      r = next_r;
    }
    q.trim();
    r.trim();
    return {q, r};
  }

  static std::pair<DecimalBigInteger, DecimalBigInteger> divmod_abs(DecimalBigInteger u, DecimalBigInteger v) {
    assert(!v.is_zero());
    if(abs_compare(u, v) < 0) return {DecimalBigInteger(0), u};
    long long norm = base / (v.a.back() + 1);
    u.mul_int(norm);
    v.mul_int(norm);
    int extra_base_shifts = 0;
    if(v.a.size() > 128 && (v.a.size() & 1)) {
      u = shift_left_digits(u, 1);
      v = shift_left_digits(v, 1);
      extra_base_shifts = 1;
    }
    auto [q, r] = divmod_abs_bz(std::move(u), std::move(v));
    if(extra_base_shifts > 0) r = high_digits(r, extra_base_shifts);
    r.div_int(norm);
    q.trim();
    r.trim();
    return {q, r};
  }

  friend std::pair<DecimalBigInteger, DecimalBigInteger> divmod(const DecimalBigInteger& x, const DecimalBigInteger& y) {
    assert(!y.is_zero());
    auto [q, r] = divmod_abs(x.abs(), y.abs());
    q.sign = x.sign * y.sign;
    r.sign = x.sign;
    q.trim();
    r.trim();
    return {q, r};
  }

  friend DecimalBigInteger operator/(const DecimalBigInteger& x, const DecimalBigInteger& y) {
    return divmod(x, y).first;
  }
  friend DecimalBigInteger operator%(const DecimalBigInteger& x, const DecimalBigInteger& y) {
    return divmod(x, y).second;
  }
  DecimalBigInteger& operator/=(const DecimalBigInteger& v) { return *this = *this / v; }
  DecimalBigInteger& operator%=(const DecimalBigInteger& v) { return *this = *this % v; }

  friend std::istream& operator>>(std::istream& is, DecimalBigInteger& v) {
    std::string s;
    is >> s;
    v.read(s);
    return is;
  }
  friend std::ostream& operator<<(std::ostream& os, const DecimalBigInteger& v) {
    return os << v.to_string();
  }
};

#endif // HARUILIB_MATH_DECIMAL_BIG_INTEGER_HPP
