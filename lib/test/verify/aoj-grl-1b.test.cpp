#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/courses/library/5/GRL/1/GRL_1_B"
#include "template/template.hpp"
#include <vector>

#include "graph/bellmanford.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int V,E,r; cin >> V >> E >> r;
  vector<Edge<ll>>edges;
  for (int i=0; i<E; i++) {
    int s,t; ll d;
    cin >> s >> t >> d;
    edges.emplace_back(s,t,d);
  }

  vector<ll> ans = bellman_ford(edges,V,r);
  for (int i=0; i<V; i++) if (ans[i] < -LLINF) {
    cout << "NEGATIVE CYCLE\n";
    return 0;
  }

  for (int i=0; i<V; i++) {
    if (ans[i] >= LLINF) cout << "INF\n";
    else cout << ans[i] << "\n";
  }
  return 0;
}
