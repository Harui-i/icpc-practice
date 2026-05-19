#define PROBLEM "https://judge.yosupo.jp/problem/gcd_convolution"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "convolution/multiple-zeta-moebius-transform.hpp"

using mint = modint998244353;

mint op(mint a, mint b) {
  return a + b;
}

mint invop(mint a, mint b) {
  return a - b;
}

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N; cin >> N;
  vector<mint>a(N+1); for(int i=0; i<N; i++) cin >> a[i+1];
  vector<mint>b(N+1); for(int i=0; i<N; i++) cin >> b[i+1];  

  vector<mint> za = multiple::zeta_transform_naive<mint,op>(a);
  vector<mint> zb = multiple::zeta_transform_naive<mint,op>(b);

  vector<mint> zc(N+1); for(int i=0; i<N+1; i++) zc[i] = za[i] * zb[i];

  vector<mint> c = multiple::moebius_transform_naive<mint,invop>(zc);
  for(int i=1; i<=N; i++) cout << c[i].val() << " \n"[i==N];
}