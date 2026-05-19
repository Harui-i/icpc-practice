---
title: Bellmanford(ベルマンフォード法)
documentation_of: //graph/bellmanford.hpp
---

負辺のあるグラフでも最短距離を求められるアルゴリズム。
めちゃめちゃ参考にしました: [https://ei1333.github.io/library/graph/shortest-path/bellman-ford.hpp](https://ei1333.github.io/library/graph/shortest-path/bellman-ford.hpp)

## bellman_ford
```
vector<T> bellman_ford(const vector<Edge<T>>& edges, int N, int start)
```

ベルマンフォード法を行い、頂点`start`から各頂点`v`までの最短距離が格納された`vector`
である`dist`を返す。

`dist[v]`は、vが到達できない頂点のとき正の無限大が格納され、`start`から`v`までの経路に負の閉路があったときは負の無限大が格納される。

無限大と書いたが、実際には型`T`で表せる最大/最小の数が使われている。

### 計算量

頂点数を $V$、辺の数を$E$として
- $ O(VE) $

