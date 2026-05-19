#define PROBLEM "https://judge.yosupo.jp/problem/tree_diameter"

#include "template/template.hpp"
#include "graph/graph_template.hpp"
#include "graph/diameter.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int N; cin >> N;
  Graph<ll>graph(N);
  for(int i=0; i<N-1; i++) {
    ll a, b, c; cin >> a >> b >> c;
    graph.add_edge(a,b,c);
    graph.add_edge(b,a,c);
  }

  pair<vector<int>, ll> pr = mylib::diameter_path<ll>(graph);

  cout << pr.second << " " << pr.first.size() << "\n";
  for(int i=0; i<(int)pr.first.size(); i++) {
    cout << pr.first[i];
    if (i < N-1) cout << " ";
    else cout << "\n";
  }

  return 0;
}
