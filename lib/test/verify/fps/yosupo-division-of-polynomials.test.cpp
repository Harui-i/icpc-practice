#define PROBLEM "https://judge.yosupo.jp/problem/division_of_polynomials"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "formal-power-series/formal-power-series.hpp"
#include "formal-power-series/fps-998.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N, M; cin >> N >> M;

  FPS<mint> f(N); for(int i=0; i<N; i++) cin >> f[i];
  FPS<mint> g(M); for(int i=0; i<M; i++) cin >> g[i];

  FPS quotient = f / g;
  FPS remainder = f % g;
  int u = quotient.size();
  int v = remainder.size();
  cout << u << " " << v << "\n";
  for(int i=0; i<u; i++) cout << quotient[i] << " ";
  cout << "\n";

  for(int i=0; i<v; i++) cout << remainder[i] << " ";
  cout << "\n";

}

