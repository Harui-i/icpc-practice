#define PROBLEM "https://judge.yosupo.jp/problem/general_weighted_matching"

#include "template/template.hpp"
#include "graph/general_weighted_matching.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int N, M; cin >> N >> M;
  mylib::GeneralWeightedMatching wm(N);
  for (int i = 0; i < M; i++) {
    int u, v;
    long long w;
    cin >> u >> v >> w;
    wm.add_edge(u, v, w);
  }

  auto ans = wm.solve();
  vector<pair<int, int>> edges;
  for (int i = 0; i < N; i++) {
    if (ans.second[i] != -1 && i < ans.second[i]) edges.emplace_back(i, ans.second[i]);
  }

  cout << edges.size() << " " << ans.first << "\n";
  for (auto [u, v] : edges) {
    cout << u << " " << v << "\n";
  }
  return 0;
}
