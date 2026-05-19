#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "template/template.hpp"

#include "structure/fenwick_tree.hpp"
#include "graph/tree/heavy_light_decomposition.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, Q; cin >> N >> Q;
  vector<int>a(N); 
  for(int i=0; i<N; i++) cin >> a[i];

  HaruiLib::HLD hld(N);
  for (int i=0; i<N-1; i++) {
    int u, v; cin >> u >> v;
    hld.graph.add_edge(u,v);
    hld.graph.add_edge(v,u);
  }

  hld.build();
  fenwick_tree<ll> fw(N);
  for (int i=0; i<N; i++) {
    fw.add(hld.id[i], a[i]);
  }

  for (int q=0; q<Q; q++) {
    int op; cin >> op;
    if (op == 0) {
      int p, x; cin >> p >> x;
      fw.add(hld.id[p], x);
    }
    else if (op == 1) {
      int u, v; cin >> u >> v;
      ll ret = 0;

      for (HaruiLib::Interval interval : hld.get_path(u, v)) {
        ret += fw.sum(interval.top_id, interval.bottom_id + 1);
      }

      cout << ret << endl;
    }
  }

  return 0;
}
