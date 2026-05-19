#ifndef HARUILIB_MATH_EXTERNAL_GCD_HPP
#define HARUILIB_MATH_EXTERNAL_GCD_HPP

#include <tuple>

// g,x,y
template<typename T>
constexpr std::tuple<T, T, T> extendedGCD(T a, T b) {
    T x0 = 1, y0 = 0, x1 = 0, y1 = 1;
    while (b != 0) {
        T q = a / b;
        T r = a % b;
        a = b;
        b = r;
        
        T xTemp = x0 - q * x1;
        x0 = x1;
        x1 = xTemp;
        
        T yTemp = y0 - q * y1;
        y0 = y1;
        y1 = yTemp;
    }
    return {a, x0, y0};
}
#endif // HARUILIB_MATH_EXTERNAL_GCD_HPP
