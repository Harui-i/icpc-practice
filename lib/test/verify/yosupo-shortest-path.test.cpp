#define PROBLEM "https://judge.yosupo.jp/problem/shortest_path" 

#include "template/template.hpp"
#include "graph/graph_template.hpp"
#include "graph/dijkstra.hpp"

#include <algorithm>

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, M, s, t; cin >> N >> M >> s >> t;

  Graph<ll> gr(N);
  for(int i=0; i<M; i++) {
    ll a, b, c;
    cin >> a >> b >> c;
    gr.add_edge(a,b,c);
  }

  vector<ll>dist; vector<int>prev;

   auto pr = dijkstra_path(gr, s);
   dist = pr.first; prev = pr.second;

  if (dist[t] > LLINF) {
    cout << -1 << "\n";
  }
  else {
    ll X = dist[t];
    int Y;
    vector<int> path;
    {
      int now = t;
      while (now != -1) {
        path.push_back(now);
        now = prev[now];
      }
      Y = path.size();
    }

    reverse(path.begin(), path.end());
    cout << X << " " << Y - 1 << "\n";
    for(int i=0; i<Y-1; i++) {
      cout << path[i] << " " << path[i+1] << "\n";
    }
  }

}
