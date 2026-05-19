#ifndef HARUILIB_MATH_MODINT2611_HPP
#define HARUILIB_MATH_MODINT2611_HPP

#include <random>
#include <chrono>
/*
法が2^61 - 1のmodint
cf: https://qiita.com/keymoon/items/11fac5627672a6d6a9f6
 */

struct modint2611 {

  constexpr static const uint64_t mod = (1ull << 61ull) - 1;
  using uint128_t = __uint128_t;
  uint64_t _val;

  constexpr explicit modint2611() : _val(0) {}

  constexpr explicit modint2611(uint64_t v) : _val(v) {
    if (_val >= mod) _val -= mod;
  }

  constexpr modint2611& operator+=(const modint2611& rhs) {
    if ((_val += rhs._val) >= mod) _val -= mod;
    return *this;
  }

  constexpr modint2611& operator-=(const modint2611& rhs) {
    if (_val < rhs._val) {
      _val += (mod - rhs._val);
    }
    else {
      _val += -rhs._val;
    }
    return *this;
  }

  constexpr modint2611& operator*=(const modint2611& rhs) {
    uint128_t c = (uint128_t) _val * rhs._val;
    // return (c>>61) + (c & mod);
    uint64_t d = (c>>61) + (c & mod);
    if (d >= mod) d -= mod;

    _val = d;
    return *this;
  }
  
  constexpr modint2611 operator-() const { return modint2611(0) - *this; }

  constexpr modint2611 operator+(const modint2611& a) const {
    return modint2611(*this) += a;
  }

  constexpr modint2611 operator-(const modint2611& a) const {
    return modint2611(*this) -= a;
  }

  constexpr modint2611 operator*(const modint2611& a) const {
    return modint2611(*this) *= a;
  }
  
  constexpr bool operator==(const modint2611& a) const { return _val == a._val; }

  constexpr bool operator!=(const modint2611& a) const { return _val != a._val; }

  constexpr uint64_t val() const {
    return _val;
  }

  constexpr modint2611 pow(uint64_t n) const {
    modint2611 ret = modint2611(1);
    modint2611 base = *this;
    while (n) {
      if (n & 1) ret *= base;
      base *= base;
      n >>= 1;
    }
    return ret;
  }

  constexpr modint2611 inv() const {
    return (*this).pow(mod - 2);
  }

  static inline modint2611 generate_base() {
    mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution< uint64_t > rand(1, mod - 1);

    return modint2611(rand(mt));
  }

};

#endif // HARUILIB_MATH_MODINT2611_HPP
