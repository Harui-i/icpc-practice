#define PROBLEM "https://judge.yosupo.jp/problem/addition_of_big_integers"

#include "template/template.hpp"
#include "math/big_integer.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int T; cin >> T;
  while(T--) {
    BigInteger a, b;
    cin >> a >> b;
    cout << a + b << '\n';
  }
}
