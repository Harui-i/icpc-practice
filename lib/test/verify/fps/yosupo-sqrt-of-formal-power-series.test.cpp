#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"

#include "template/template.hpp"
#include "math/modint.hpp"
using mint = modint998244353;

#include "formal-power-series/fps-998.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int N; cin >> N;
  FPS<mint> f(N);
  for (int i = 0; i < N; i++) cin >> f[i];

  FPS<mint> g = f.sqrt(N);
  if (g.size() == 0) {
    cout << -1 << '\n';
    return 0;
  }

  for (int i = 0; i < N; i++) {
    cout << g[i].val() << " \n"[i == N - 1];
  }
}
