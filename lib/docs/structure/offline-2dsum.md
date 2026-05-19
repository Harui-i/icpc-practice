---
title: Offline 2D Sum (Rectangle Sum)
documentation_of: //structure/offline_2dsum.hpp
---

2次元平面上の点に重みを加え、長方形領域内の重みの総和を求めるクエリをオフラインで処理します。

## コンストラクタ

```
offline_2dsum<T, W>()
```
T: 座標の型, W: 重みの型

## add_point

```
void add_point(T x, T y, W w)
```
点 $(x, y)$ に重み $w$ を追加する。

### 計算量
- $O(1)$

## add_query

```
void add_query(T l, T r, T d, T u)
```
領域 $[l, r) \times [d, u)$ の重みの総和を求めるクエリを追加する。
つまり、$l \le x < r, d \le y < u$ を満たす点の重みの総和を求める。

### 計算量
- $O(1)$

## solve

```
std::vector<W> solve()
```
追加されたすべてのクエリに対する解答を計算し、追加された順に返す。

### 計算量
点の個数を $N$、クエリの個数を $Q$ とすると
- $O(N \log N + Q \log Q + (N + Q) \log N)$