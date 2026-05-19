---
title: General Weighted Matching
documentation_of: //graph/general_weighted_matching.hpp
---

一般グラフの最大重みマッチング（Blossom / 花アルゴリズム）を解く。
重み付き辺を受け取り、重み和が最大となるマッチングを返す。
辺重みは非負整数を想定する。

## 使い方

```cpp
mylib::GeneralWeightedMatching wm(N);
wm.add_edge(u, v, w);
auto [sum, mate] = wm.solve();
```

- `sum`: 最大重み
- `mate[i]`: 頂点 `i` とマッチした頂点番号（未マッチは `-1`）

同じ 2 頂点間に複数回 `add_edge` した場合は、最大の重みだけを使う。

## 計算量

- $O(N^3)$
