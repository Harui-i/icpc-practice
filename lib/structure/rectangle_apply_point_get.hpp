#ifndef HARUILIB_STRUCTURE_RECTANGLE_APPLY_POINT_GET_HPP
#define HARUILIB_STRUCTURE_RECTANGLE_APPLY_POINT_GET_HPP

#include <cassert>
#include <vector>

template <class F, F (*composition)(F, F), F (*id)(), class T = int>
struct rectangle_apply_point_get {
  rectangle_apply_point_get(T xl, T xr, T yl, T yr)
      : xl(xl), xr(xr), yl(yl), yr(yr), root(-1) {
    assert(xl < xr);
    assert(yl < yr);
    root = new_x_node();
  }

  void apply(T l, T r, T d, T u, F f) {
    assert(xl <= l && l <= r && r <= xr);
    assert(yl <= d && d <= u && u <= yr);
    apply_x(root, xl, xr, l, r, d, u, f);
  }

  F get(T x, T y) const {
    assert(xl <= x && x < xr);
    assert(yl <= y && y < yr);
    return get_x(root, xl, xr, x, y);
  }

private:
  struct XNode {
    int left, right, y_root;
  };

  struct YNode {
    int left, right;
    F val;
  };

  int new_x_node() {
    xs.push_back({-1, -1, -1});
    return (int)xs.size() - 1;
  }

  int new_y_node() {
    ys.push_back({-1, -1, id()});
    return (int)ys.size() - 1;
  }

  void apply_x(int k, T nl, T nr, T ql, T qr, T qd, T qu, F f) {
    if (qr <= nl || nr <= ql) return;
    if (ql <= nl && nr <= qr) {
      xs[k].y_root = apply_y(xs[k].y_root, yl, yr, qd, qu, f);
      return;
    }

    T mid = nl + (nr - nl) / 2;
    if (ql < mid) {
      if (xs[k].left == -1) {
        int child = new_x_node();
        xs[k].left = child;
      }
      apply_x(xs[k].left, nl, mid, ql, qr, qd, qu, f);
    }
    if (mid < qr) {
      if (xs[k].right == -1) {
        int child = new_x_node();
        xs[k].right = child;
      }
      apply_x(xs[k].right, mid, nr, ql, qr, qd, qu, f);
    }
  }

  int apply_y(int k, T nl, T nr, T ql, T qr, F f) {
    if (qr <= nl || nr <= ql) return k;
    if (k == -1) k = new_y_node();
    if (ql <= nl && nr <= qr) {
      ys[k].val = composition(f, ys[k].val);
      return k;
    }

    T mid = nl + (nr - nl) / 2;
    if (ql < mid) ys[k].left = apply_y(ys[k].left, nl, mid, ql, qr, f);
    if (mid < qr) ys[k].right = apply_y(ys[k].right, mid, nr, ql, qr, f);
    return k;
  }

  F get_x(int k, T nl, T nr, T x, T y) const {
    if (k == -1) return id();

    F res = get_y(xs[k].y_root, yl, yr, y);
    if (nr - nl == 1) return res;

    T mid = nl + (nr - nl) / 2;
    if (x < mid) return composition(get_x(xs[k].left, nl, mid, x, y), res);
    return composition(get_x(xs[k].right, mid, nr, x, y), res);
  }

  F get_y(int k, T nl, T nr, T y) const {
    if (k == -1) return id();

    F res = ys[k].val;
    if (nr - nl == 1) return res;

    T mid = nl + (nr - nl) / 2;
    if (y < mid) return composition(get_y(ys[k].left, nl, mid, y), res);
    return composition(get_y(ys[k].right, mid, nr, y), res);
  }

  T xl, xr, yl, yr;
  int root;
  std::vector<XNode> xs;
  std::vector<YNode> ys;
};

#endif // HARUILIB_STRUCTURE_RECTANGLE_APPLY_POINT_GET_HPP
