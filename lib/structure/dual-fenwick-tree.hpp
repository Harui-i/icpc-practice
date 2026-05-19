#ifndef HARUILIB_STRUCTURE_DUAL_FENWICK_TREE_HPP
#define HARUILIB_STRUCTURE_DUAL_FENWICK_TREE_HPP

#include <cassert>
#include <vector>

template <class T> struct dual_fenwick_tree {
public:
  dual_fenwick_tree(): _n(0) {}
  explicit dual_fenwick_tree(int n): _n(n), data(n) {}

  // point sum
  T sum(int p) {
    assert(0 <= p && p < _n);
    T ret = T(0);
    p++;
    while (p <= _n) {
      ret += data[p-1];
      p += p & -p;
    }

    return ret;
  }

  void add(int l, int r, T x) {
     assert(0 <= l && l <= r && r <= _n);
     add(r, x);
     add(l, -x);
  }
private:
  int _n;
  std::vector<T> data;
  void add(int r, T x) {
    while (r > 0) {
      data[r-1] += x;
      r -= r & -r;
    }
    
  }
};

#endif // HARUILIB_STRUCTURE_DUALFENWICK_TREE_HPP
