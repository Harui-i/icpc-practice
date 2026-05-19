#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"
#include "template/template.hpp"

#include <vector>
#include "structure/fenwick_tree.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, Q; cin >> N >> Q;

  fenwick_tree<ll> fw(N);
  for (int i=0; i<N; i++) {
    int a; cin >> a;
    fw.add(i, a);
  }

  for (int q=0; q<Q; q++) {
    ll op, a, b; cin >> op >> a >> b;
    if (op == 0) {
      fw.add(a,b);
    }
    else {
      cout << fw.sum(a,b) << endl;
    }
  }
  return 0;
}
