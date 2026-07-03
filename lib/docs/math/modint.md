---
title: modint
documentation_of: //math/modint.hpp
---

なんかうまくやってくれます。生成AIが書いてくれました。

## mod_sqrt

```
long long mod_sqrt(long long a, long long p)
```

$x^2 \equiv a \pmod p$ となる $x$ を1つ返す。存在しない場合は `-1` を返す。

`p` は素数であることを仮定している。

### 計算量

- $O(\log^2 p)$

## static_modint::sqrt

```
long long sqrt_val()
static_modint sqrt()
```

`sqrt_val()` は固定された mod で平方根を求め、存在しない場合は `-1` を返す。

`sqrt()` は平方根が存在することを仮定して `static_modint` で返す。
