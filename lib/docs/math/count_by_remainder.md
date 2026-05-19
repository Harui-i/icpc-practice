---
title: count by remainder
documentation_of: //math/count_by_remainder.hpp
---

$L$ 以上 $R$未満であって、$M$で割った余りが$b$である整数の個数を求める。
こんなんソラで書くのは頭バグらせますからね。

## count_by_remainder

```
T count_by_remainder(T l, T r, T b, T M)
```

### 計算量

- $O(1)$

###　実装例

verify先がAtCしかみつからなかったので。

```C++
#include "math/count_by_remainder.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  ll A,M,L,R; cin >> A >> M >> L >> R;
  A %= M;
  if (A < 0) A += M;  

  cout << count_by_remainder(L,R+1,A,M) << endl;
  return 0;
}
```


問題:  [https://atcoder.jp/contests/abc334/submissions/54631702] ( https://atcoder.jp/contests/abc334/submissions/54631702 )
