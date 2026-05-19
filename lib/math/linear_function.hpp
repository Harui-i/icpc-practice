#ifndef HARUILIB_LINEAR_FUNCTION_HPP
#define HARUILIB_LINEAR_FUNCTION_HPP

template <typename T>
struct LinearFunction {
  T a, b;

  LinearFunction() : a{0}, b(0) {}
  LinearFunction(T _a, T _b) : a(_a), b(_b) {}

  static LinearFunction Add_Identity() {
    return LinearFunction(T(0), T(0));
  }

  static LinearFunction Mul_Identity(){
    return LinearFunction(T(1), T(0));
  }

  // f(g())
  LinearFunction composite(LinearFunction& g) const {
    return LinearFunction(a * g.a, a * g.b + b);
  }

  LinearFunction operator+(const LinearFunction& rhs) const {
    return LinearFunction(a + rhs.a, b + rhs.b);
  }

  // rhs(f())
  LinearFunction operator*(const LinearFunction& rhs) const {
    LinearFunction f = *this;
    return rhs.composite(f);
  }

  T operator()(T x) const {
    return a * x + b;
  }

};


#endif // HARUILIB_LINEAR_FUNCTION_HPP