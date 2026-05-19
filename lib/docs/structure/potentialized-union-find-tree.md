---
title: Potentialized Union Find Tree (ポテンシャルつきUnionFind木)
documentation_of: //structure/potentialized-union-find-tree.hpp
---


## コンストラクタ

```
PotentializedUnionFindTree<T, op, invop, e>()
```
T: 群(の載ってる集合), op: 二項演算, invop: 二項演算の逆元, e: 二項演算の単位元を返す関数。

# merge

```
int merge(int a, int b, T t)
```
aのポテンシャル - bのポテンシャルが`t`になるように併合する。

### 計算量
- ならし $ (O(\alpha(n))) $

# diff 

```
T diff(int a, int b)
```
aのポテンシャル - bのポテンシャルを計算する。


### 計算量
- ならし $ (O(\alpha(n))) $

