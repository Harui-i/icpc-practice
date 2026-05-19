#define PROBLEM "https://judge.yosupo.jp/problem/bitwise_and_convolution"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "convolution/superset-zeta-moebius-transform.hpp"

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
  vector<mint> A(1 << N); for (int i = 0; i < 1 << N; i++) cin >> A[i];
  vector<mint> B(1 << N); for (int i = 0; i < 1 << N; i++) cin >> B[i];

  // Aを上位集合についてのゼータ変換する
  vector<mint> AZ = superset_zeta_transform<mint,op>(A);
  // Bを上位集合についてゼータ変換する
  vector<mint> BZ = superset_zeta_transform<mint,op>(B);

  vector<mint>C(1 << N); for (int i = 0; i < 1 << N; i++) C[i] = AZ[i] * BZ[i];
  // Cを上位集合についてのメビウス変換する。
  vector<mint>CZ = superset_moebius_transform<mint,invop>(C);
  for (int i = 0; i < 1 << N; i++) cout << CZ[i].val() << " \n"[i == (1 << N) - 1];
}