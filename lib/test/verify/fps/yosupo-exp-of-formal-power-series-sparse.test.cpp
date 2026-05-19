#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse"

#include "formal-power-series/formal-power-series.hpp"
#include "formal-power-series/fps-998.hpp"
#include "formal-power-series/fps-sparse.hpp"
#include "math/modint.hpp"
#include "template/template.hpp"

using mint = modint998244353;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  cout.tie(0);
  int N, K;
  cin >> N >> K;
  FPS<mint> f(N);
  for (int i = 0; i < K; i++) {
    int a, x;
    cin >> a >> x;
    f[a] = mint(x);
  }

  cout << f.exp_sparse(N) << endl;
}
