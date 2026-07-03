#ifndef HARUILIB_MATH_MODINT_HPP
#define HARUILIB_MATH_MODINT_HPP

#include "math/external_gcd.hpp"
#include <type_traits>
#include <cassert>

long long mod_pow_ll(long long x, long long n, long long mod) {
    long long ret = 1;
    while (n > 0) {
        if (n & 1) ret = (__int128)ret * x % mod;
        x = (__int128)x * x % mod;
        n >>= 1;
    }
    return ret;
}

// x^2 = a (mod p) となる x を返す。存在しない場合は -1。
// p は素数であることを仮定する。
long long mod_sqrt(long long a, long long p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return 0;
    if (p == 2) return a;
    if (mod_pow_ll(a, (p - 1) / 2, p) != 1) return -1;
    if (p % 4 == 3) return mod_pow_ll(a, (p + 1) / 4, p);

    long long q = p - 1;
    int s = 0;
    while ((q & 1) == 0) {
        q >>= 1;
        s++;
    }

    long long z = 2;
    while (mod_pow_ll(z, (p - 1) / 2, p) != p - 1) z++;

    long long c = mod_pow_ll(z, q, p);
    long long x = mod_pow_ll(a, (q + 1) / 2, p);
    long long t = mod_pow_ll(a, q, p);
    int m = s;

    while (t != 1) {
        int i = 1;
        long long tt = (__int128)t * t % p;
        while (tt != 1) {
            tt = (__int128)tt * tt % p;
            i++;
        }
        long long b = c;
        for (int j = 0; j < m - i - 1; j++) b = (__int128)b * b % p;
        x = (__int128)x * b % p;
        c = (__int128)b * b % p;
        t = (__int128)t * c % p;
        m = i;
    }

    return x;
}

template<int MOD, typename T = int>
struct static_modint {
    T value;

    constexpr explicit static_modint() : value(0) {}

    static constexpr int mod() { return MOD; }

    constexpr static_modint(long long v) {
        if constexpr (std::is_same<T, double>::value) {
            value = double(v);
        }
        else {
            value = int(((v % MOD) + MOD) % MOD);
        }
    }

    constexpr static_modint& operator+=(const static_modint& other) {
        if constexpr (std::is_same<T, double>::value) {
            value += other.value;
        }
        else {
            if ((value += other.value) >= MOD) value -= MOD;
        }
        return *this;
    }

    constexpr static_modint& operator-=(const static_modint& other) {
        if constexpr (std::is_same<T, double>::value) {
            value -= other.value;
        }
        else {
            if ((value -= other.value) < 0) value += MOD;
        }
        return *this;
    }

    constexpr static_modint& operator*=(const static_modint& other) {
        if constexpr (std::is_same<T, double>::value) {
            value *= other.value;
        }
        else {
            value = int((long long)value * other.value % MOD);
        }
        return *this;
    }

    constexpr static_modint operator+(const static_modint& other) const {
        return static_modint(*this) += other;
    }

    constexpr static_modint operator-(const static_modint& other) const {
        return static_modint(*this) -= other;
    }

    constexpr static_modint operator-() const {
        return static_modint(0) - *this;
    }

    constexpr static_modint operator*(const static_modint& other) const {
        return static_modint(*this) *= other;
    }

    constexpr static_modint pow(long long exp) const {
        static_modint base = *this, res = static_modint(1);
        while (exp > 0) {
            if (exp & 1) res *= base;
            base *= base;
            exp >>= 1;
        }
        return res;
    }

    long long sqrt_val() const {
        return mod_sqrt(value, MOD);
    }

    static_modint sqrt() const {
        long long ret = sqrt_val();
        assert(ret != -1);
        return static_modint(ret);
    }

    constexpr static_modint inv() const {
        if constexpr (std::is_same<T, double>::value) {
            static_modint ret;
            ret.value = double(1.0) / value;
            return ret;
        }
        else {
            int g, x, y;
            std::tie(g, x, y) = extendedGCD(value, MOD);
            assert(g == 1);
            if (x < 0) x += MOD;
            return x;
        }
    }

    constexpr static_modint& operator/=(const static_modint& other) {
        return *this *= other.inv();
    }

    constexpr static_modint operator/(const static_modint& other) const {
        return static_modint(*this) /= other;
    }

    constexpr bool operator!=(const static_modint& other) const {
        return val() != other.val();
    }

    constexpr bool operator==(const static_modint& other) const {
        return val() == other.val();
    }

    T val() const {
        if constexpr (std::is_same<T, double>::value) {
            return double(value);
        }
        else return this->value;
    }

    friend std::ostream& operator<<(std::ostream& os, const static_modint& mi) {
        return os << mi.value;
    }

    friend std::istream& operator>>(std::istream& is, static_modint& mi) {
        long long x;
        is >> x;
        mi = static_modint(x);
        return is;
    }
};

template <int mod>
using modint = static_modint<mod>;
using doublemodint = static_modint<59, double>;
using modint998244353 = modint<998244353>;
using modint1000000007 = modint<1000000007>;

#endif // HARUILIB_MATH_MODINT_HPP
