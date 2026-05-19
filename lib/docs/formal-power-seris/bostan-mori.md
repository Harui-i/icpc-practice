---
title: Bostan-Mori法
documentation_of: //formal-power-series/bostan-mori.hpp
---

線形漸化式の第N項や、形式的べき級数の分数 P(x)/Q(x) の係数を高速に求めるアルゴリズム。

## 使い方

```
mint BostanMori(FPS<mint> P, FPS<mint> Q, unsigned long long N)
```

P(x) / Q(x) の x^N の係数を返す。Q[0] != 0 が必要。

```
mint BostanMori(const vector<mint>& a, const vector<mint>& c, unsigned long long N)
```

a_0..a_{K-1} と
a_{n+K} = c_1 a_{n+K-1} + ... + c_K a_n
が与えられたときの a_N を返す。

内部で Q(x) = 1 - c_1 x - ... - c_K x^K とし、
P(x) = (A(x) Q(x)) mod x^K を作って Bostan-Mori に流している。

## 計算量
畳み込みが FFT/NTT で高速化されるなら
- O(K log K log N)

ナイーブな畳み込みなら
- O(K^2 log N)

## 参考
- https://qiita.com/ryuhe1/items/da5acbcce4ac1911f47a
