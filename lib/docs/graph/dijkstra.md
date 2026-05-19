---
title: Dijkstra(ダイクストラ法)
documentation_of: //graph/dijkstra.hpp
---

負辺のないグラフでの最短距離を求めるアルゴリズム。
負辺があっても負閉路がない場合は正しい答えを返すが、計算量はめちゃめちゃ悪くなるらしい。
cf: [https://theory-and-me.hatenablog.com/entry/2019/09/08/182442](https://theory-and-me.hatenablog.com/entry/2019/09/08/182442)

## dijkstra
```
vector<T> dijkstra(const Graph<T>& graph, int start)
```

`start`からの各頂点`v`までの最短距離が`dist[v]`に入っているような`vector`である`dist`を返す。
到達不可能な頂点については、最短距離は無限大となっている(実際には、型`T`で表せる最大のもの)。


### 計算量
頂点の数を$V$、辺の数を$E$として

- $O(E \log V)$ $(E+V) \log V$とする文献(`Wikipedia`など)もあるけど、大抵$E >= V$なので結局おなじ何だと思う[^1]

[^1] : 要考察