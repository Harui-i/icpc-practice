---
title: Formal Power Series (形式的べき級数)
documentation_of: //formal-power-series/formal-power-series.hpp
---

modによらない(さすがに合成数とかだと厳しいが)共通した処理を実装している。

## コンストラクタ
```
FPS(vector<mint> vec)
```
はい

```
FPS(initializer_list<mint> ilist)
```
波括弧とかで初期化するやつにも対応！

```
FPS(int sz)
```
項の数で初期化(最大の次数とは1ズレる)


## diff
微分。

### 計算量
mintが四則演算 $O(1)$ なら、
- $O\left(N\right)$


## integral
積分。

### 計算量
mintが四則演算 $O(1)$ なら、
- $O\left(N\right)$

## inv系

### 計算量
下の3つのどれも、FPSのサイズ(最大次数+1)を $N$ として
- $O(N \log N)$

### inv_fast2
これが最速のはず。
Library Checkerでは500msほど。


### inv_fast1
逆元を(体数倍の分だけ)速めに求める
Library Checkerでは650msほど。
→もういらないかも

### inv_naive
逆元を(定数倍の分だけ)遅めに求める
Library Checkerでは920msほど。

## log
logを求める。定数項が`1`であることを要求する。

### 計算量
$O(N \log N)$

## exp
expを求める。定数項が`0`であることを要求する。
~~現在はバグっている！~~ → 治りました`

### 計算量

- $O(N \log N)$


## pow

累乗を求める。定数項がどうとかそういった面倒な制約はない。


## 多項式の除算と余り

`%`や`/`が演算子オーバーロードにより実装されているので、それを使う。

### 計算量
$f$の次数を$N$,$g$の次数を$M$として $f/g$の商と余りを、
- $O((N+M)\log(N+M) + M\log M)$
で求められる。

## 疎なFPSの場合の高速化

FPSの非ゼロな項が少ない（スパースである）場合、いくつかの操作は $O(N \log N)$ よりも高速に行うことができます。
これらの操作は `fps-sparse.hpp` に実装されており、`FPS` クラスのメンバ関数として呼び出すことができます。

- `mul_sparse(g, deg)`: スパースな `g` との乗算
- `inv_sparse(deg)`: 逆元
- `exp_sparse(deg)`: 指数関数
- `log_sparse(deg)`: 対数関数
- `pow_sparse(k, deg)`: 累乗

詳細については、[fps-sparse(疎な場合の高速化)](./fps-sparse.md) のドキュメントを参照してください。