#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"

#include "template/template.hpp"
#include "math/modint.hpp"
using mint = modint998244353;

#include "formal-power-series/fps-998.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N; ll M; cin >> N >> M;

  FPS<mint> f(N); for(int i=0; i<N; i++) cin >> f[i];

  FPS<mint> ret = f.pow(M, N);
  for(int i=0; i<N; i++) {
    cout << ret[i].val() << " \n"[i == N-1];
  }

  return 0;
}
