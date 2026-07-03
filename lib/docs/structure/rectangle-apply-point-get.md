---
title: Rectangle Apply Point Get
documentation_of: //structure/rectangle_apply_point_get.hpp
---

長方形領域に作用素を掛け、一点に掛かっている作用素を取得するデータ構造です。

座標範囲を先に指定し、その範囲内の長方形作用と一点取得をオンラインに処理できます。

作用素 `F` はモノイドとして扱います。

```
F composition(F f, F g)
F id()
```

`composition(f, g)` は ACL の `lazy_segtree` と同じく、作用 `g` の後に作用 `f` を適用する合成、`id()` は単位元です。

## コンストラクタ

```
rectangle_apply_point_get<F, composition, id, T = int>(T xl, T xr, T yl, T yr)
```

座標範囲 $[xl, xr) \times [yl, yr)$ を指定する。
`T` は座標の型です。

## apply

```
void apply(T l, T r, T d, T u, F f)
```

領域 $[l, r) \times [d, u)$ に作用 `f` を掛ける。

### 計算量
座標範囲の幅を $X = xr - xl, Y = yr - yl$ として
- $O(\log X \log Y)$

新しく作られる内部ノード数も $O(\log X \log Y)$。

## get

```
F get(T x, T y)
```

点 `(x, y)` に掛かっている作用素の合成を返す。

### 計算量
座標範囲の幅を $X = xr - xl, Y = yr - yl$ として
- $O(\log X \log Y)$

内部ノードは作らない。
