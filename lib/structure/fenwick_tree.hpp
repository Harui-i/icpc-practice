#ifndef HARUILIB_STRUCTURE_FENWICK_TREE_HPP
#define HARUILIB_STRUCTURE_FENWICK_TREE_HPP

#include <vector>
#include <cassert>

template <class T> struct fenwick_tree {
  fenwick_tree(): _n(0) {}
  explicit fenwick_tree(int n): _n(n), data(n) {}

  // point add
  void add(int p, T x) {
    assert(0 <= p && p < _n);
    p++;
    while (p <= _n) {
      data[p-1] += T(x);
      p += p & -p;
    }
  } 

  T sum(int l, int r) {
    assert(0 <= l && l <= r && r <= _n);
    return sum(r) - sum(l);
  }

private:
  int _n;
  std::vector<T> data;
  T sum(int r) {
    T ret(0);
    while (r > 0) {
      ret += data[r-1];
      r -= r & -r;
    }

    return ret;
  }
};

#endif // HARUILIB_STRUCTURE_FENWICK_TREE_HPP
