---
title: primality_test
documentation_of: //math/primality_test.hpp
---

64bit 整数に対する素数判定です。

決定的 Miller-Rabin を使っています。

## 使い方

```cpp
bool is_prime(unsigned long long n);
```

`n` が素数なら `true`、そうでなければ `false` を返します。

## 計算量

`O(log n)`
