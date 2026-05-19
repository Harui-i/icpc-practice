#define PROBLEM "https://judge.yosupo.jp/problem/primality_test"

#include "template/template.hpp"
#include "math/primality_test.hpp"

int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);

  int Q; cin >> Q;
  while(Q--) {
    unsigned long long n; cin >> n;
    cout << (is_prime(n) ? "Yes" : "No") << '\n';
  }
}
