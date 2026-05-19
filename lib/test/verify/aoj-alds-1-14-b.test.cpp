#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
#include "template/template.hpp"

#include <string>

#include "string/rolling-hash.hpp"


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  string T, P;
  cin >> T >> P;

  using mint = modint2611;
  mint base = mint::generate_base();

  RollingHash rlh_t(T,base);
  RollingHash rlh_p(P,base);
  Hash b = rlh_p.get(0, int(P.size()));

  for (int i=0; i+int(P.size()) <= int(T.size()); i++) {
    Hash a = rlh_t.get(i, i+int(P.size()));
    if (a == b) {
      cout << i << endl;
    }
  }
  return 0;
}
