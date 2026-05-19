#define PROBLEM "https://judge.yosupo.jp/problem/convolution_mod"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "formal-power-series/fps-998.hpp"

using mint = modint998244353;


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, M; cin >> N >> M;
  FPS<mint> a(N); for(int i=0; i<N; i++) cin >> a[i];
  FPS<mint> b(M); for(int i=0; i<M; i++) cin >> b[i];

  FPS<mint> c = a * b;
  for(int i=0; i<c.size(); i++) cout << c[i].val() << " \n"[i == c.size()-1];
}
