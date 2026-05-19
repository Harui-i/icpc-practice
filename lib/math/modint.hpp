#ifndef HARUILIB_MATH_MODINT_HPP
#define HARUILIB_MATH_MODINT_HPP

#include "math/external_gcd.hpp"
#include <type_traits>
#include <cassert>

template<int MOD, typename T = int>
struct static_modint {
    T value;

    constexpr explicit static_modint() : value(0) {}

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
