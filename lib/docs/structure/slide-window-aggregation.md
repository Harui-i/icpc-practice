---
title: Foldable Deque(Slide Window Aggregation)
documentation_of: //structure/slide-window-aggregation.hpp
---

単位元があって、結合的な演算(逆元は必要なし)(可換じゃなくてもいいよ(!!))について、両端キュー(Deque)っぽい操作と、Deque内の要素の総積が(ならしも入れて) $O(1)$ で計算できるデータ構造です。セグ木でいいかも。


名称についてはSlide Window Aggregation(SWAG)というのも結構覇権だけど、https://qiita.com/Shirotsume/items/4a2837b5895ef9a7aeb1 の記事がFoldable Dequeという名称を推していたのでそれを採用してる。

## 計算量解析について

あとはまかせた: 

https://noshi91.hatenablog.com/entry/2019/10/10/230032

## コンストラクタ
```
FoldableDeque<S, op, e>()
```
S: モノイド, op: 二項演算, e: 二項演算の単位元を返す関数。


## push_back
dequeっぽく扱える。
### 計算量
- $O(1)$

## push_front
dequeっぽく扱える。

### 計算量
- $O(1)$

## pop_front
dequeっぽく扱える。

### 計算量
- $O(1)$ (ならし)

## pop_back
dequeっぽく扱える。

### 計算量
- $O(1)$ (ならし)

## all_prod
```
S all_prod()
```

Deque内にある要素の(先頭側から末尾側の順に計算した)総積を返す。

### 計算量
- $O(1)$
これがスゴイポイントであるけど、セグ木でいいじゃんかも。