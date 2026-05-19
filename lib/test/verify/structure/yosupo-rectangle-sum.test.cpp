#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "template/template.hpp"
#include "structure/offline_2dsum.hpp"

#include <vector>

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, Q; cin >> N >> Q;
  offline_2dsum<int, ll> g;
  for (int i=0; i<N; i++) {
    int x, y; cin >> x >> y;
    ll w; cin >> w;
    g.add_point(x, y, w);
  }

  for (int q=0; q<Q; q++) {
    int l, d, r, u;
    cin >> l >> d >> r >> u;
    g.add_query(l, r, d, u);
  }

  auto ans = g.solve();
  for (auto x : ans) cout << x << "\n";

  return 0;
}
