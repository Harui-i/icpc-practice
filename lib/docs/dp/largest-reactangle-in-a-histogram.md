---
title: ヒストグラム内の最大長方形
documentation_of: //dp/largest-rectangle-in-a-histogram.hpp
---

## 概要

ヒストグラム内の最大長方形を求める。お気持ちはコメントに書いてあるのでそれを参照してくれ。

番長とか先輩とかいうワードは、[スライド最大（最小）値・ヒストグラム内最大長方形問題を俯瞰する](https://qiita.com/kuuso1/items/318d42cd089a49eeb332)
という記事によるもの。

## largest_reactangle_in_a_histogram
```
ll largest_reactangle_in_a_histogram<vector<T>& vec>
```

vec内の最大長方形の面積を求める

### 計算量
O(N)
