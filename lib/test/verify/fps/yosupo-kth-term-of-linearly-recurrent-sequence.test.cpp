#define PROBLEM "https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "formal-power-series/formal-power-series.hpp"
#include "formal-power-series/fps-998.hpp"

#include "formal-power-series/fiduccia.hpp"

using mint = modint998244353;


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int d; cin >> d;
  ll K; cin >> K;
  vector<mint>a(d); for(int i=0; i<d; i++) cin >> a[i];
  vector<mint>c(d); for(int i=0; i<d; i++) cin >> c[i];

  mint ans = Fiduccia(a,c,K);

  cout << ans.val() << "\n";


}
