#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_mod"

#include "template/template.hpp"
#include "math/modint.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int T; cin >> T;
  while (T--) {
    long long y, p; cin >> y >> p;
    cout << mod_sqrt(y, p) << '\n';
  }
}
