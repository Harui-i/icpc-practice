---
title: Cumulative Sum 2D (二次元累積和)
documentation_of: //dp/cumulative-sum-2d.hpp
---

## コンストラクタ

```
CumulativeSum2D< T >(int H, int W)
```
1. サイズ$H$ * $W$ の二次元グリッドを作成する。

### 計算量
- $O(1)$

## add
```
void add(int i, int j, T x)
```

座標 $(i,j)$に$x$を加算する。

### 制約
- $0 \leq i \lt H, 0 \leq j \lt W $ 
(だけどassertしてません。したほうがいいね)

### 計算量
- O(1)

## build
```
void build()
```
二次元累積和を計算する。
### 計算量
- $O(1)$

## query
```
T query(int si, int sj, int gi, int gj)
```

直積(?) $[si, gi) \times [sj, gj)の区間和を求める (0-indexed)。

### 制約
- $0 \leq si \lt H $
- $0 \leq sj \lt W $
- $0 \leq gi \leq H $
- $0 \leq gj \leq W $  
- `build()`が呼ばれた後に呼ばれる必要がある

(だけどassertしてません。したほうがいいね)


### 計算量
- $O(1)$
