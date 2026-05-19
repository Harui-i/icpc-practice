#define PROBLEM "https://judge.yosupo.jp/problem/inverse_matrix"

#include "template/template.hpp"
#include "math/modint.hpp"
#include "math/matrix/matrix.hpp"

using mint = modint998244353;


int main() {
  ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
  int N; cin >> N;

  Matrix<mint>A(N,N);

  for(int i=0; i<N; i++) for(int j=0; j<N; j++) cin >> A[i][j];
  Matrix<mint> inv = A.inverse();
  if (inv.size().first == 0) {
    cout << -1 << endl;
  }
  else {
    for(int i=0; i<N; i++) {
      for(int j=0; j<N; j++) {
        cout << inv[i][j].val();
        if (j != N-1) cout << " ";
        else cout << endl;
      }
    }
  }
}
