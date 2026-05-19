#define PROBLEM "https://judge.yosupo.jp/problem/division_of_big_integers"

#include "template/template.hpp"
#include "math/big_integer.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int T; cin >> T;
  while(T--) {
    BigInteger a, b;
    cin >> a >> b;
    auto [q, r] = divmod(a, b);
    cout << q << ' ' << r << '\n';
  }
}
