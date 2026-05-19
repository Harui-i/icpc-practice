#ifndef HARUILIB_LIBRARY_STRUCTURE_SLIDE_WINDOW_AGGREGATION_HPP
#define HARUILIB_LIBRARY_STRUCTURE_SLIDE_WINDOW_AGGREGATION_HPP

#include <vector>
#include <algorithm>

template <class S, S (*op)(S, S), S (*e)()>
struct FoldableDeque {
  struct Node {
    S val;
    S prod;
  };

  std::vector<Node> front, back;

  FoldableDeque() : front(), back() {}
  size_t size() const { return front.size() + back.size(); }
  bool empty() const { return front.size() + back.size() == 0; }


  // nyaanさんのをパクっており
  void rebalance() {
    int n = front.size() + back.size();
    int s0 = n / 2 + (front.empty() ? n % 2 : 0);
    // frontにs0個
    // backにN - s0個入れる
    vector<Node> a{front};
    std::reverse(begin(a), end(a));
    std::copy(begin(back), end(back), back_inserter(a));
    front.clear(), back.clear();
    for (int i = s0 - 1; i >= 0; i--) push_front(a[i].val);
    for (int i = s0; i < n; i++) push_back(a[i].val);
    return;
  }

  S all_prod() const {
    if (front.empty() && back.empty() ) return e();

    if (front.empty()) {
      return back.back().prod;
    }
    else if (back.empty()) {
      return front.back().prod;
    }

    else return op(front.back().prod, back.back().prod) ;
  }

  void push_back(const S& x) {
    if (back.empty()) {
      back.push_back({x, x});
    }
    else {
      // 順序怪しいかも
      back.push_back({x, op(back.back().prod, x) });
    }
  }

  void push_front(const S& x) {
    if (front.empty()) {
      front.push_back({x, x});
    }
    else {
      // 順序怪しいかも
      front.push_back({x, op(x, front.back().prod) });
    }  
  }

  void pop_back() {
    assert(size() > 0);
    if (back.empty()) rebalance();
    back.pop_back();
  }

  void pop_front() {
    assert(size() > 0);
    if (front.empty()) rebalance();
    front.pop_back();
  }
};
#endif // HARUILIB_LIBRARY_STRUCTURE_SLIDE_WINDOW_AGGREGATION_HPP