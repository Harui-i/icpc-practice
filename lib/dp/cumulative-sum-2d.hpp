#ifndef HARUILIB_DP_CUMULATIVE_SUM_2D_HPP
#define HARUILIB_DP_CUMULATIVE_SUM_2D_HPP

#include <cassert>
#include <vector>

template<class T>
struct CumulativeSum2D {
  bool has_built = false;
  int H, W;
  std::vector<std::vector<T>> data;

  CumulativeSum2D(int _H, int _W)  : H(_H), W(_W), data(std::vector<std::vector<T>>(H+1, std::vector<T>(W+1))) {
  }

  void add (int i, int j, T x) {
    assert(0 <= i && i < H && 0 <= j && j < W && !has_built);
    data[i+1][j+1] += x;
  }

  // https://ngtkana.hatenablog.com/entry/2023/12/04/194327
  // 1B
  void build() {
    assert(!has_built);
    for (int i=1; i<=H; i++) {
      for (int j=1; j<=W; j++) {
        data[i][j] += data[i-1][j];
      }
    }

    for (int i=1; i<=H; i++) {
      for (int j=1; j<=W; j++) {
        data[i][j] += data[i][j-1];
      }
    }


    has_built = true;
  }

  // [si, gi) * [sj, gj)
  T query(int si, int sj, int gi, int gj) {
    assert(has_built);
    assert(0 <= si && si < H && 0 <= sj && sj < W);
    assert(0 <= gi && gi <= H && 0 <= gj && gj <= W);
    assert(si <= gi && sj <= gj);
    return data[gi][gj] - data[si][gj] - data[gi][sj] + data[si][sj];
  }
};
#endif //HARUILIB_DP_CUMULATIVE_SUM_2D_HPP