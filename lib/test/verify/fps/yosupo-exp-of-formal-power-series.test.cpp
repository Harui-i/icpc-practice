#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "formal-power-series/formal-power-series.hpp"
#include "formal-power-series/fps-998.hpp"

using mint = modint998244353;


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N; cin >> N;
  vector<modint998244353>a(N);
  for(int i=0; i<N; i++) cin >> a[i];

  FPS a_fps(a);
  cout << a_fps.exp(N) << endl;

}
