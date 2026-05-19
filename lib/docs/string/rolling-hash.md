---
title: ローリングハッシュ(Rolling Hash)
documentation_of: //string/rolling-hash.hpp
---

RollingHashを扱う。

文字列Sのハッシュは、$ \Sum_{i=0, 1, \dots |S|} b^i S[i] $とする。

# Hash

文字列のハッシュを表現する。
文字列の長さ、基数、ハッシュの値を持つ。

## コンストラクタ

```
Hash(mint _hash, mint _base, int _len)
```

ハッシュした値が`_hash`で、基数が`_base`であり、その文字列は`_len`の長さであるとしてハッシュを初期化する。

```
operator+(const Hash& rhs) const
```

rhsを文字列として右から結合したあとのHashを返す。
基数が同じであることを要求する。

# RollingHash

文字列のHashを扱う。先頭からのハッシュを管理しておくことで、部分文字列のハッシュ計算なども対応する。

## コンストラクタ

```
RollingHash(const string& S, mint _base): (_base)
```

## get

```
Hash get(int l, int r) const
```

$S$の$[l,r)$部分のハッシュを計算する。
$mod$は定数なので計算量は$O(1)$

